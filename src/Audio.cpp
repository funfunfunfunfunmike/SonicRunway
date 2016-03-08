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

using namespace essentia;
using namespace standard;

SrAudio::SrAudio(int sampleRate, int bufferSize) :
    _sampleRate(sampleRate),
    _bufferSize(bufferSize),
    _numMelBands(40)  // hard coded in ofxAubio
{
    essentia::init();
    AlgorithmFactory & factory = AlgorithmFactory::instance();
    
    _bandPass = factory.create("BandPass",
                               "sampleRate", _sampleRate,
                            "bandwidth", 200,
                               "cutoffFrequency", 500);
    _inputBuffer.resize(_bufferSize);
    _bandPassBuffer.resize(_bufferSize);
    
    _bandPass->input("signal").set(_inputBuffer);
    _bandPass->output("signal").set(_bandPassBuffer);
    
    //_lowOnset.setup("default", _bufferSize, _bufferSize/2, _sampleRate);
    _lowOnset.setup("mkl", _bufferSize, _bufferSize/2, _sampleRate);
    
    _beat.setup("default", _bufferSize, _bufferSize/2, _sampleRate);
    _bands.setup("default", _bufferSize, _bufferSize/2, _sampleRate);
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
}

void
SrAudio::UpdateEvents(const SrTime & now)
{
    _currentEvents.clear();
    if (_beat.received()) {
        _currentEvents.push_back(Beat);
    }
    if (_lowOnset.received()) {
        _currentEvents.push_back(LowOnset);
    }
}

void
SrAudio::AudioOut(float *output, int bufferSize, int nChannels)
{
    // XXX only handling mono for now.
    for(int i=0; i < bufferSize; i++) {
        output[i*nChannels] = _bandPassBuffer[i];
        //output[i*nChannels] = _inputBuffer[i];
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
