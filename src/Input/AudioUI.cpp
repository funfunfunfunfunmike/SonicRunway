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

SrAudioUI::SrAudioUI(SrAudio * audio, float x, float y) :
    _audio(audio)
{
    _audio = audio;
    
    _beatGui.setup("SrAudioBeat", "settings.xml", x, y);
    _beatGui.add(_bpmSlider.setup("bpm", 0, 0, 250));
   
    x += 250;
    _onsetGui.setup("SrAudioOnset", "settings.xml", x + 10, 10);
    _onsetGui.add(_gotOnsetSlider.setup("onset", 0, 0, 250));
    _onsetGui.add(_onsetThresholdSlider.setup("threshold", 0, 0, 2));
    _onsetGui.add(_onsetNoveltySlider.setup(
                  "onset novelty", 0, 0, 10000));
    _onsetGui.add(_onsetThresholdedNoveltySlider.setup(
                  "thr. novelty", 0, -1000, 1000));
    
    // Set a default value for the slider (assignment op overloaded)
    _onsetThresholdSlider =
        _audio->GetLowOnsetHistory().GetThreshold()[0];
    
    x += 250;
    
    _bandsGui.setup("SrAudioMelBends", "settings.xml", x + 10, 115);
    /*
    for (int i = 0; i < 40; i++) {
        _bandPlot.addVertex(50 + i * 650 / 40.,
                            240 - 100 *
                            _audio->GetCurrentFftValues()[i]);
    }
     */
}

SrAudioUI::~SrAudioUI()
{
    
}

void
SrAudioUI::Update()
{
    const SrOnsetHistory & onset =
        _audio->GetLowOnsetHistory();
    
    _onsetNoveltySlider = onset.GetNovelty()[0];
    _onsetThresholdedNoveltySlider = onset.GetThresholdedNovelty()[0];
    _bpmSlider = _audio->GetBeatHistory().GetBpm()[0];
}

void
SrAudioUI::Draw()
{
    _beatGui.draw();
    _onsetGui.draw();
    
    ofPushStyle();
    
    ofSetColor(ofColor::orange);
    ofSetLineWidth(3.0);
    _bandsGui.draw();
    for (int i = 0; i < _bandPlot.size(); i++) {
        _bandPlot[i].y = 240 - 100 * _audio->GetCurrentFftValues()[i];
    }
    _bandPlot.draw();
    
    ofPopStyle();
}