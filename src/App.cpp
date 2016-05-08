//
//  App.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/13/16.
//
//

#include "App.hpp"
#include "ofApp.h"

#include "BeatPattern.hpp"
#include "FftPattern.hpp"
#include "ExamplePattern.hpp"
#include "StripesPattern.hpp"

extern "C" void CGSSetDebugOptions(int);
extern "C" void CGSDeferredUpdates(int);

SrApp::SrApp() :
    _model(),
    _audio(&_model),
    _audioUI(&_audio),
    _artnet(&_model),
    _previs(&_model, &_audio),
    _uiColumnWidth(220),
    _uiMargin(10)
{
    ofSetFrameRate(_model.ComputeFramesPerSecond());
    
    // Disable vertical sync so FPS can be greater than 60.
    ofSetVerticalSync(false);
    CGSSetDebugOptions(0x08000000);
    CGSDeferredUpdates(true);
    
    _globalPanel.setup("Global");
    _globalPanel.setPosition(_uiMargin,_uiMargin);
    
    _patternPanel.setup("Patterns");
    _patternPanel.setPosition(_uiMargin + _uiColumnWidth, _uiMargin);
    
    ofSoundStreamSetup(_model.GetNumChannels(), _model.GetNumChannels(),
                       _model.GetSampleRate(), _model.GetBufferSize(), 4);
    
    _globalPanel.add(_previs.GetUiPanel());
    _globalPanel.add(_audioUI.GetUiPanel());
    
    SrExamplePattern *examplePattern =
        new SrExamplePattern("Example Pattern", &_model, &_audio);
    _AddPattern(examplePattern);
    examplePattern->SetEnabled(false);
    
    SrBeatPattern * beatPattern =
        new SrBeatPattern("Beat Pattern", &_model, &_audio);
    _AddPattern(beatPattern);
    
    SrFftPattern *fftPattern =
        new SrFftPattern("Fft Pattern", &_model, &_audio);
    _AddPattern(fftPattern);
    
    SrStripesPattern *stripesPattern =
        new SrStripesPattern("Stripes Pattern", &_model, &_audio);
    _AddPattern(stripesPattern);
    stripesPattern->SetEnabled(false);
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
    for(auto iter = _patterns.begin(); iter != _patterns.end(); iter++) {
        SrPattern *pattern = *iter;
        pattern->Update();
    }
    
    _audioUI.Update();
    _previs.Update();
    
    std::string fpsStr = "frame rate: "
            + ofToString(ofGetTargetFrameRate(), 2)
            + " / " + ofToString(ofGetFrameRate(), 2);
    ofSetWindowTitle(fpsStr);
}

void
SrApp::Draw()
{
    _model.Clear();
    _model.BeginDrawing();
    
    for(auto iter = _patterns.begin(); iter != _patterns.end(); iter++) {
        SrPattern *pattern = *iter;
        pattern->Draw();
    }
    
    _model.EndDrawing();
    
    ofBackground(40,40,40);
    
    _model.RenderFrameBuffer(_uiMargin + _uiColumnWidth * 2, _uiMargin,
                             _uiColumnWidth * 2, 75);
    
    _globalPanel.draw();
    _patternPanel.draw();
    
    _previs.Draw(_uiMargin + _uiColumnWidth * 2, 100,
                 1280, 720);
    
    _artnet.UpdateLights();
}