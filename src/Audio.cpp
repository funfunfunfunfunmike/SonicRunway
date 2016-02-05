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
#include "Settings.hpp"

#include "ofMain.h"
#include "ofxAubio.h"
#include "ofxGui.h"

using namespace essentia;
using namespace standard;

SrAudio::SrAudio(const SrSettings & settings) :
    _sampleRate(settings.GetSampleRate()),
    _bufferSize(settings.GetBufferSize())
{
    essentia::init();
    AlgorithmFactory & factory = AlgorithmFactory::instance();
    
    _bandPass = factory.create("BandPass",
                               "sampleRate", _sampleRate,
                               "bandwidth", 100,
                               "cutoffFrequency", 200);
    
    _inputBuffer.resize(_bufferSize);
    _bandPassBuffer.resize(_bufferSize);
                        
    _bandPass->input("signal").set(_inputBuffer);
    _bandPass->output("signal").set(_bandPassBuffer);
    
    _onset.setup("default", _bufferSize, _bufferSize/2, _sampleRate);
    _beat.setup("default", _bufferSize, _bufferSize/2, _sampleRate);
    _bands.setup("default", _bufferSize, _bufferSize/2, _sampleRate);
}

SrAudio::~SrAudio()
{
    delete _bandPass;
    
    essentia::shutdown();
}

void
SrAudio::Update()
{
    
}

void
SrAudio::AudioIn(float *input, int bufferSize, int nChannels)
{
    // Copy left channel audio into mono input buffer
    for(int i=0; i < bufferSize; i++) {
        _inputBuffer[i] = input[i * nChannels];
    }
    
    _bandPass->compute();
    
    _onset.audioIn(&_bandPassBuffer[0], bufferSize, nChannels);
    _beat.audioIn(input, bufferSize, nChannels);
    _bands.audioIn(input, bufferSize, nChannels);
}

void
SrAudio::AudioOut(float *output, int bufferSize, int nChannels)
{
    // XXX only handling mono for now.
    for(int i=0; i < bufferSize; i++) {
        output[i*nChannels] = _bandPassBuffer[i];
    }
}

bool
SrAudio::BeatReceived()
{
    return _beat.received();
}

float
SrAudio::GetBPM() const
{
    return _beat.bpm;
}

float
SrAudio::GetOnsetThreshold() const
{
    return _onset.threshold;
}

void
SrAudio::SetOnsetThreshold(float threshold)
{
    _onset.threshold = threshold;
}

bool
SrAudio::OnsetReceived()
{
    return _onset.received();
}

float
SrAudio::GetOnsetNovelty() const
{
    return _onset.novelty;
}

float
SrAudio::GetOnsetThresholdedNovelty() const
{
    return _onset.thresholdedNovelty;
}

float *
SrAudio::GetBandsEnergies() const
{
    return _bands.energies;
}
