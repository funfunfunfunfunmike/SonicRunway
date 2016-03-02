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
    _bufferSize(bufferSize)
{
    essentia::init();
    AlgorithmFactory & factory = AlgorithmFactory::instance();
    
    _lowPass = factory.create("LowPass",
                               "sampleRate", _sampleRate,
                               "cutoffFrequency", 1500);
    _midPass = factory.create("BandPass",
                               "sampleRate", _sampleRate,
                               "bandwidth", 3500,
                               "cutoffFrequency", 5000);
    _highPass = factory.create("HighPass",
                               "sampleRate", _sampleRate,
                               "cutoffFrequency", 5000);
    
    _inputBuffer.resize(_bufferSize);
    _lowPassBuffer.resize(_bufferSize);
    _midPassBuffer.resize(_bufferSize);
    _highPassBuffer.resize(_bufferSize);
    
    _lowPass->input("signal").set(_inputBuffer);
    _lowPass->output("signal").set(_lowPassBuffer);
    _midPass->input("signal").set(_inputBuffer);
    _midPass->output("signal").set(_midPassBuffer);
    _highPass->input("signal").set(_inputBuffer);
    _highPass->output("signal").set(_highPassBuffer);
    
    _lowOnset.setup("default", _bufferSize, _bufferSize/2, _sampleRate);
    _midOnset.setup("default", _bufferSize, _bufferSize/2, _sampleRate);
    _highOnset.setup("default", _bufferSize, _bufferSize/2, _sampleRate);
    _beat.setup("default", _bufferSize, _bufferSize/2, _sampleRate);
    _bands.setup("default", _bufferSize, _bufferSize/2, _sampleRate);
}

SrAudio::~SrAudio()
{
    delete _lowPass;
    delete _midPass;
    delete _highPass;
    
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
    
    _lowPass->compute();
    _midPass->compute();
    _highPass->compute();
    
    _lowOnset.audioIn(&_lowPassBuffer[0], bufferSize, nChannels);
    _midOnset.audioIn(&_midPassBuffer[0], bufferSize, nChannels);
    _highOnset.audioIn(&_highPassBuffer[0], bufferSize, nChannels);
    _beat.audioIn(input, bufferSize, nChannels);
    _bands.audioIn(input, bufferSize, nChannels);
    
}

void
SrAudio::UpdateEvents()
{
    _currentEvents.clear();
    if (_beat.received()) {
        _currentEvents.push_back(Beat);
    }
    if (_lowOnset.received()) {
        _currentEvents.push_back(LowOnset);
    }
    if (_midOnset.received()) {
        _currentEvents.push_back(MidOnset);
    }
    if (_highOnset.received()) {
        _currentEvents.push_back(HighOnset);
    }
}

void
SrAudio::AudioOut(float *output, int bufferSize, int nChannels)
{
    // XXX only handling mono for now.
    for(int i=0; i < bufferSize; i++) {
        output[i*nChannels] = _lowPassBuffer[i];
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
    _lowOnset.threshold = threshold;
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

const std::vector<SrAudio::Event> &
SrAudio::GetCurrentEvents() const
{
    return _currentEvents;
}