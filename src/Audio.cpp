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
    _beatHistory(model)
{
    // Allocate one float buffer for each FFT band
    for (size_t i = 0; i < 40; i++) {
        _ffts.push_back(
            SrFloatBuffer(model, SrFrequencyOncePerAudioIn));
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
}

void
SrAudio::AudioIn(float *input, int bufferSize, int nChannels)
{
    // Copy left channel audio into mono input buffer
    for(int i=0; i < bufferSize; i++) {
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

void
SrAudio::AudioOut(float *output, int bufferSize, int nChannels)
{
    // XXX only handling mono for now.
    for(int i=0; i < bufferSize; i++) {
        //output[i*nChannels] = _bandPassBuffer[i];
        output[i*nChannels] = _inputBuffer[i];
    }
}
