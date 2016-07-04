//
//  Audio.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/9/16.
//
//  Based on the example by Paul Brossier included in ofxAubio:
//  https://github.com/aubio/ofxAubio
//

#include "Audio.hpp"

#include "ofMain.h"
#include "ofxAubio.h"
#include "ofxGui.h"
#include "Model.hpp"

using namespace essentia;
using namespace standard;

SrAudio::SrAudio(SrModel * model) :
    _model(model),
    _lowOnsetHistory(model),
    _beatHistory(model),
    _outputDelayed(false),
    _fullAudioBufferIndex(0)
{
    // Allocate one float buffer for each FFT band
    for (size_t i = 0; i < 40; i++) {
        _ffts.push_back(
            SrFloatBuffer(model, SrFrequencyOncePerAudioIn));
    }
    
    // Allocate the full audio buffer, with enough space to
    // store delayed audio for the full length of the runway.
    _fullAudioBuffer.resize(model->GetBuffersPerSecond() *
                            model->GetMaxBufferDuration());
    for(size_t i=0; i<_fullAudioBuffer.size(); i++) {
        _fullAudioBuffer[i].resize(model->GetBufferSize());
    }
    
    essentia::init();
    AlgorithmFactory & factory = AlgorithmFactory::instance();
    
    int sampleRate = _model->GetSampleRate();
    int bufferSize = _model->GetBufferSize();
    
    _bandPass = factory.create("BandPass",
                               "sampleRate", sampleRate,
                            "bandwidth", 200,
                               "cutoffFrequency", 500);
    _inputBuffer.resize(bufferSize);
    _bandPassBuffer.resize(bufferSize);
    
    _bandPass->input("signal").set(_inputBuffer);
    _bandPass->output("signal").set(_bandPassBuffer);
    
    int hopSize = bufferSize / 2;
    
    _bands.setup("default", bufferSize, hopSize, sampleRate);
}

SrAudio::~SrAudio()
{
    delete _bandPass;
    
    essentia::shutdown();
    
    // XXX delete / exit aubio stuff?
}

const SrOnsetHistory &
SrAudio::GetLowOnsetHistory() const
{
    return _lowOnsetHistory;
}

const SrBeatHistory &
SrAudio::GetBeatHistory() const
{
    return _beatHistory;
}

const vector<SrFloatBuffer> &
SrAudio::GetFfts() const
{
    return _ffts;
}

std::vector<float>
SrAudio::GetCurrentFftValues() const
{
    std::vector<float> ret;
    for(size_t i=0; i < _ffts.size(); i++) {
        ret.push_back(_ffts[i][0]);
    }
    
    return ret;
}

void
SrAudio::AudioIn(float *input, int bufferSize, int nChannels)
{
    // Increment full audio buffer index, and loop around if
    // we get to the end.
    _fullAudioBufferIndex--;
    if (_fullAudioBufferIndex < 0) {
        _fullAudioBufferIndex = _fullAudioBuffer.size() - 1;
    }
    
    // Copy left channel audio into mono input buffer
    // XXX could maybe memcpy to be faster?
    for(int i=0; i < bufferSize; i++) {
        _fullAudioBuffer[_fullAudioBufferIndex][i] = input[i * nChannels];
        _inputBuffer[i] = input[i * nChannels];
    }
    
    _lowOnsetHistory.AudioIn(&_bandPassBuffer[0],
                            bufferSize, nChannels);
    
    _beatHistory.AudioIn(input, bufferSize, nChannels);
    
    _bands.audioIn(input, bufferSize, nChannels);
    
    // Run audio analysis
    _bandPass->compute();
    
    float *energies = _bands.energies;
    for (size_t i = 0; i < _ffts.size(); i++) {
        _ffts[i].Push(energies[i]);
    }
}

/*
void
SrAudio::AudioOut(float *output, int bufferSize, int nChannels) const
{
    // XXX only handling mono for now.
    for(int i=0; i < bufferSize; i++) {
        //output[i*nChannels] = _bandPassBuffer[i];
        output[i*nChannels] = _inputBuffer[i];
    }
}
 */

void
SrAudio::SetOutputAudioDelayed(bool sendAudioOut)
{
    _outputDelayed = sendAudioOut;
}

void
SrAudio::AudioOutDelayed(float * output, int bufferSize, int nChannels,
                         float delayInSeconds) const
{
    
    if ( ! _outputDelayed ){
        return;
    }
    
    int bufferOffset = delayInSeconds * _model->GetBuffersPerSecond();
    int thisIndex = _fullAudioBufferIndex + bufferOffset;
    thisIndex %= _fullAudioBuffer.size();
   
    const vector<float> & thisBuffer = _fullAudioBuffer[thisIndex];
    
    // XXX memcpy for speed?
    for(int i=0; i < bufferSize; i++) {
        output[i*nChannels] = thisBuffer[i];
    }
}
