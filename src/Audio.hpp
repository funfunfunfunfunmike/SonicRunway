//
//  Audio.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/9/16.
//
//  Based on the example by Paul Brossier included in ofxAubio:
//  https://github.com/aubio/ofxAubio
//

#ifndef _SR_AUDIO_HPP_
#define _SR_AUDIO_HPP_

#include <stdio.h>
#include "ofxAubio.h"

class ofApp;

///
/// SrAudio - Audio input and processing.
///
/// This is a wrapper class on the ofxAubio extension, consolidating
/// various aspects of audio processing.
///
class SrAudio {
public:
    SrAudio();
    ~SrAudio();
    
    void Update();
    
    void AudioIn(float * input, int bufferSize, int nChannels);
    
    // Beat
    bool BeatReceived();
    float GetBPM() const;
    
    // Onset
    bool OnsetReceived();
    float GetOnsetThreshold() const;
    void SetOnsetThreshold(float threshold);
    float GetOnsetThresholdedNovelty() const;
    float GetOnsetNovelty() const;
    
    // Bands
    float * GetBandsEnergies() const;
    
private:
    ofxAubioOnset _onset;
    ofxAubioBeat _beat;
    ofxAubioMelBands _bands;
};

#endif
