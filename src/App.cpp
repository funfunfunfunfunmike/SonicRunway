//
//  App.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/13/16.
//
//

#include "App.hpp"
#include "ofApp.h"

SrApp::SrApp() :
    _sampleRate(44100),
    _bufferSize(256),
    _numChannels(1),
    _model(),
    _audio(_sampleRate, _bufferSize),
    _cues(&_audio),
    _lightArray(_model),
     _audioUI(&_audio, 10.0, 10.0),
    _lowOnsetPattern(&_model, &_lightArray,
                     _cues.GetLowOnsetQueue()),
    _midOnsetPattern(&_model, &_lightArray,
                     _cues.GetMidOnsetQueue()),
    _highOnsetPattern(&_model, &_lightArray,
                      _cues.GetHighOnsetQueue()),
    _gridDisplay(&_lightArray, &_model, 10.0, 230.0, 930.0, 300.0),
    _artnet(_lightArray)
{
    ofSoundStreamSetup(_numChannels, _numChannels,
                       _sampleRate, _bufferSize, 4);
    
    _lowOnsetPattern.SetHue(100.0);
    _midOnsetPattern.SetHue(200.0);
    _highOnsetPattern.SetHue(0.0);
    
    _lowOnsetPattern.SetYRange(0.0, 0.33);
    _midOnsetPattern.SetYRange(0.33, 0.66);
    _highOnsetPattern.SetYRange(0.66, 1.0);
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
SrApp::AudioOut(float *output, int bufferSize, int nChannels)
{
    _audio.AudioOut(output, bufferSize, nChannels);
}

void
SrApp::Update()
{
    SrTime now = std::chrono::system_clock::now();
    
    _audio.Update();
    _cues.Update(now);
    
    _lightArray.Clear();
    _lowOnsetPattern.Update(now);
    _midOnsetPattern.Update(now);
    _highOnsetPattern.Update(now);
    
    _audioUI.Update();
    _gridDisplay.Update();
}

void
SrApp::Draw()
{
    ofBackground(40,40,40);
    _audioUI.Draw();
    _gridDisplay.Draw();
    _artnet.UpdateLights();
}