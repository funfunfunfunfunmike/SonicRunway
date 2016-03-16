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
#include "FftPattern.hpp"

SrApp::SrApp() :
    _model(),
    _audio(&_model),
    _audioUI(&_audio),
    _artnet(&_model),
    _previs(&_model, &_audio),
    _uiColumnWidth(220),
    _uiMargin(10)
{
    ofSetFrameRate(_model.GetFramesPerSecond());
    
    _globalPanel.setup("Global");
    _globalPanel.setPosition(_uiMargin,_uiMargin);
    
    _patternPanel.setup("Patterns");
    _patternPanel.setPosition(_uiMargin + _uiColumnWidth, _uiMargin);
    
    ofSoundStreamSetup(_model.GetNumChannels(), _model.GetNumChannels(),
                       _model.GetSampleRate(), _model.GetBufferSize(), 4);
    
    _globalPanel.add(_previs.GetUiPanel());
    _globalPanel.add(_audioUI.GetUiPanel());
    
    SrShapePattern * shapePattern =
        new SrShapePattern("OnsetPattern", &_model, &_audio);
    _AddPattern(shapePattern);
    
    SrFftPattern *fftPattern =
        new SrFftPattern("FftPattern", &_model, &_audio);
    _AddPattern(fftPattern);
}

SrApp::~SrApp()
{
    // XXX remove panels first?
    // XXX need to figure out clean pattern for deleting...
    
    /*
    for(auto iter = _patterns.begin(); iter != _patterns.end(); iter++) {
        delete *iter;
    }
     */
}

void
SrApp::_AddPattern(SrPattern * pattern)
{
    _patterns.push_back(pattern);
    _patternPanel.add(pattern->GetUiPanel());
}

void
SrApp::AudioIn(float * input, int bufferSize, int nChannels)
{
    _audio.AudioIn(input, bufferSize, nChannels);
}

void
SrApp::AudioOut(float *output, int bufferSize, int nChannels)
{
    _previs.AudioOut(output, bufferSize, nChannels);
}

void
SrApp::Update()
{
    SrTime now = std::chrono::system_clock::now();
    
    for(auto iter = _patterns.begin(); iter != _patterns.end(); iter++) {
        SrPattern *pattern = *iter;
        pattern->Update(now);
    }
    
    _audioUI.Update();
    _previs.Update();
    
    std::string fpsStr = "frame rate: " + ofToString(ofGetFrameRate(), 2);
    ofSetWindowTitle(fpsStr);
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
    
    _model.RenderFrameBuffer(_uiMargin + _uiColumnWidth * 2, _uiMargin,
                             _uiColumnWidth * 2, 75);
    
    _globalPanel.draw();
    _patternPanel.draw();
    
    _previs.Draw(_uiMargin + _uiColumnWidth * 2, 100,
                 _uiColumnWidth * 4, 750);
    
    _artnet.UpdateLights();
}