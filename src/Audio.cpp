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

void
SrAudio::Setup(ofApp *app)
{
    
    _onset.setup();
    _beat.setup();
    _bands.setup();
    
}

void
SrAudio::Update()
{
    printf("SrAudio::update\n");
    
}

void
SrAudio::Exit()
{
    
}

void
SrAudio::AudioIn(float *input, int bufferSize, int nChannels)
{
    _onset.audioIn(input, bufferSize, nChannels);
    _beat.audioIn(input, bufferSize, nChannels);
    _bands.audioIn(input, bufferSize, nChannels);
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
