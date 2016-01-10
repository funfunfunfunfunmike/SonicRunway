//
//  srAudioUI.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/10/16.
//
//  Based on the example by Paul Brossier included in ofxAubio:
//  https://github.com/aubio/ofxAubio
//

#ifndef _SR_AUDIOUI_HPP_
#define _SR_AUDIOUI_HPP_

#include <stdio.h>
#include "ofxGui.h"

class SrAudio;

class SrAudioUI {
public:
    void Setup(SrAudio * audio, float x, float y);
    void Update();
    void Draw();
    void Exit();
    
private:
    
    SrAudio *_audio;
    
    ofxPanel _beatGui;
    ofxFloatSlider _bpmSlider;
    
    ofxPanel _onsetGui;
    ofxFloatSlider _gotOnsetSlider;
    ofxFloatSlider _onsetThresholdSlider;
    ofxFloatSlider _onsetNoveltySlider;
    ofxFloatSlider _onsetThresholdedNoveltySlider;
    
    ofxPanel _bandsGui;
    ofPolyline _bandPlot;
};

#endif 
