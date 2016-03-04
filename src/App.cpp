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
    _artnet(&_model),
    _previs(&_model)
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
    _previs.Update();
}

void
SrApp::Draw()
{
    SrTime now = std::chrono::system_clock::now();
    
    // XXX not sure why this isn't drawing...
    //std::string fpsStr = "frame rate: " + ofToString(ofGetFrameRate(), 2);
    //ofDrawBitmapStringHighlight(fpsStr, 5, 5);
    
    _model.Clear();
    _model.BeginDrawing();
    
    for(auto iter = _patterns.begin(); iter != _patterns.end(); iter++) {
        SrPattern *pattern = *iter;
        pattern->Draw(now);
    }
    
    _model.EndDrawing();
    
    ofBackground(40,40,40);
    
    _model.RenderFrameBuffer(10,250, 800, 75);
    
    _audioUI.Draw();
    
    _previs.Draw(10,350,800,600);
    
    _artnet.UpdateLights();
}