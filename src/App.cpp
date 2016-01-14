//
//  App.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/13/16.
//
//

#include "App.hpp"

SrApp::SrApp() :
    _settings(),
    _audio(),
    _cues(&_audio),
    _lightArray(_settings),
     _audioUI(&_audio, 10.0, 10.0),
    _onsetPattern(&_settings, &_lightArray, &_cues),
    _gridDisplay(&_lightArray, &_settings, 10.0, 230.0, 930.0, 300.0),
    _artnet()
{
    
}

SrApp::~SrApp()
{
    
}

void
SrApp::AudioIn(float * input, int bufferSize, int nChannels)
{
    _audio.AudioIn(input, bufferSize, nChannels);
}

void
SrApp::Update()
{
    SrTime now = std::chrono::system_clock::now();
    
    _audio.Update();
    _cues.Update(now);
    
    _lightArray.Clear();
    _onsetPattern.Update(now);
    
    _audioUI.Update();
    _gridDisplay.Update();
}

void
SrApp::Draw()
{
    ofBackground(40,40,40);
    _audioUI.Draw();
    _gridDisplay.Draw();
}