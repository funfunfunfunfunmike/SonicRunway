//
//  AudioUI.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/10/16.
//
//  Based on the example by Paul Brossier included in ofxAubio:
//  https://github.com/aubio/ofxAubio
//

#include "AudioUI.hpp"

#include "Audio.hpp"

#include "ofMain.h"

void
SrAudioUI::Setup(SrAudio * audio, float x, float y)
{
    _audio = audio;
    
    _beatGui.setup("SrAudioBeat", "settings.xml", x, y);
    _beatGui.add(_bpmSlider.setup("bpm", 0, 0, 250));
   
    x += 250;
    _onsetGui.setup("SrAudioOnset", "settings.xml", x + 10, 10);
    _onsetGui.add(_gotOnsetSlider.setup("onset", 0, 0, 250));
    _onsetGui.add(_onsetNoveltySlider.setup(
                  "onset novelty", 0, 0, 10000));
    _onsetGui.add(_onsetThresholdedNoveltySlider.setup(
                  "thr. novelty", 0, -1000, 1000));
    
    // Set a default value for the slider (assignment op overloaded)
    _onsetThresholdSlider = _audio->GetOnsetThreshold();
    
    x += 250;
    
    _bandsGui.setup("SrAudioMelBends", "settings.xml", x + 10, 115);
    for (int i = 0; i < 40; i++) {
        _bandPlot.addVertex(50 + i * 650 / 40.,
                            240 - 100 * _audio->GetBandsEnergies()[i]);
    }
}

void
SrAudioUI::Exit()
{
    
}

void
SrAudioUI::Update()
{
    // Not exactly MVC pattern!
    _audio->SetOnsetThreshold(_onsetThresholdSlider);
    
    _onsetNoveltySlider = _audio->GetOnsetNovelty();
    _onsetThresholdedNoveltySlider =
        _audio->GetOnsetThresholdedNovelty();
    _bpmSlider = _audio->GetBPM();
}

void
SrAudioUI::Draw()
{
    // update beat info
    if (_audio->BeatReceived()) {
        ofSetColor(ofColor::green);
        ofRect(90,150,50,50);
    }
    
    // update onset info
    if (_audio->OnsetReceived()) {
        ofSetColor(ofColor::red);
        ofRect(250 + 90,150,50,50);
        _gotOnsetSlider = 1;
    } else {
        _gotOnsetSlider = 0;
    }
    
    _beatGui.draw();
    _onsetGui.draw();
    
    ofSetColor(ofColor::orange);
    ofSetLineWidth(3.0);
    _bandsGui.draw();
    for (int i = 0; i < _bandPlot.size(); i++) {
        _bandPlot[i].y = 240 - 100 * _audio->GetBandsEnergies()[i];
    }
    _bandPlot.draw();
}