//
//  App.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/13/16.
//
//

#include "App.hpp"
#include "ofApp.h"

#include "ShapePattern.hpp"

SrApp::SrApp() :
    _sampleRate(44100),
    _bufferSize(256),
    _numChannels(1),
    _model(),
    _audio(_sampleRate, _bufferSize),
    _audioUI(&_audio, 10.0, 10.0),
    _artnet(&_model)
{
    ofSoundStreamSetup(_numChannels, _numChannels,
                       _sampleRate, _bufferSize, 4);
    
    _patterns.push_back(new SrShapePattern(&_model, &_audio));
}

SrApp::~SrApp()
{
    for(auto iter = _patterns.begin(); iter != _patterns.end(); iter++) {
        delete *iter;
    }
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
    
    _audio.UpdateEvents();
    
    for(auto iter = _patterns.begin(); iter != _patterns.end(); iter++) {
        SrPattern *pattern = *iter;
        pattern->Update(now);
    }
    
    _audioUI.Update();
}

void
SrApp::Draw()
{
    SrTime now = std::chrono::system_clock::now();
    
    _model.Clear();
    _model.BeginDrawing();
    
    for(auto iter = _patterns.begin(); iter != _patterns.end(); iter++) {
        SrPattern *pattern = *iter;
        pattern->Draw(now);
    }
    
    _model.EndDrawing();
    
    ofBackground(40,40,40);
    
    _model.RenderFrameBuffer(10,300, 800, 200);
    
    _audioUI.Draw();
    
    _artnet.UpdateLights();
}