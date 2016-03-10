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
    _numMelBands(40), // hard coded in ofxAubio
    _lastLowOnsetTime(0),
    _lastBeatTime(0),
    _lastThumpTime(0),
    _lowOnsetBuffer(model, SrFloatBuffer::OncePerAudioIn)
{
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
    _lowOnset.setup("default", bufferSize, hopSize, sampleRate);
    
    _beat.setup("default", bufferSize, hopSize, sampleRate);
    _bands.setup("default", bufferSize, hopSize, sampleRate);
}

SrAudio::~SrAudio()
{
    delete _bandPass;
    
    essentia::shutdown();
    
    // XXX delete / exit aubio stuff?
}

void
SrAudio::AudioIn(float *input, int bufferSize, int nChannels)
{
    // Copy left channel audio into mono input buffer
    for(int i=0; i < bufferSize; i++) {
        _inputBuffer[i] = input[i * nChannels];
    }
    
    _bandPass->compute();
    _lowOnset.audioIn(&_bandPassBuffer[0], bufferSize, nChannels);
    _beat.audioIn(input, bufferSize, nChannels);
    _bands.audioIn(input, bufferSize, nChannels);
    
    /*
    if (_lowOnset.received()) {
        _lowOnsetBuffer.Push(0.0);
    } else {
        float timeSinceOffset =
            _lowOnsetBuffer[0] + _lowOnsetBuffer.GetSecondsPerEntry();
        _lowOnsetBuffer.Push(timeSinceOffset);
    }
     */
}

void
SrAudio::UpdateEvents(const SrTime & now)
{
    uint64_t elapsedTime = ofGetElapsedTimeMillis();
    
    _currentEvents.clear();
    if (_beat.received()) {
        _currentEvents.push_back(Beat);
        _lastBeatTime = elapsedTime;
    }
    if (_lowOnset.received()) {
        _currentEvents.push_back(LowOnset);
        _lastLowOnsetTime = elapsedTime;
    }
    
    if (elapsedTime - _lastThumpTime > 500) {
        int diff = _lastBeatTime - _lastLowOnsetTime;
        if (abs(diff) < 100) {
            _currentEvents.push_back(Thump);
            _lastThumpTime = elapsedTime;
        }
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

float
SrAudio::GetBPM() const
{
    return _beat.bpm;
}

float
SrAudio::GetOnsetThreshold() const
{
    return _lowOnset.threshold;
}

void
SrAudio::SetOnsetThreshold(float threshold)
{
    _lowOnset.setThreshold(threshold);
}

float
SrAudio::GetOnsetNovelty() const
{
    return _lowOnset.novelty;
}

float
SrAudio::GetOnsetThresholdedNovelty() const
{
    return _lowOnset.thresholdedNovelty;
}

float *
SrAudio::GetBandsEnergies() const
{
    return _bands.energies;
}

int
SrAudio::GetNumMelBands() const
{
    return _numMelBands;
}

const std::vector<SrAudio::Event> &
SrAudio::GetCurrentEvents() const
{
    return _currentEvents;
}
