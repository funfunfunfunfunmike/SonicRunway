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

#include <essentia/essentia.h>
#include <essentia/algorithmfactory.h>

class ofApp;
class SrSettings;

// XXX this should be defined in essentia somewhere..
typedef float Real;

///
/// SrAudio - Audio input and processing.
///
/// This is a wrapper class on the ofxAubio extension, consolidating
/// various aspects of audio processing.
///
class SrAudio {
public:
    SrAudio(const SrSettings &settings);
    ~SrAudio();
    
    void Update();
    
    void AudioIn(float * input, int bufferSize, int nChannels);
    void AudioOut(float * output, int bufferSize, int nChannels);
    
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
    int _sampleRate;
    int _bufferSize;
    
    essentia::standard::Algorithm *_bandPass;
    
    ofxAubioOnset _onset;
    ofxAubioBeat _beat;
    ofxAubioMelBands _bands;
    
    vector<Real> _inputBuffer;
    vector<Real> _bandPassBuffer;
};

#endif
