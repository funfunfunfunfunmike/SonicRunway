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
    SrAudio(int sampleSize, int bufferSize);
    ~SrAudio();
    
    void Update();
    
    void AudioIn(float * input, int bufferSize, int nChannels);
    void AudioOut(float * output, int bufferSize, int nChannels);
    
    // Beat
    bool BeatReceived();
    float GetBPM() const;
    
    // Onset
    float GetOnsetThreshold() const;
    void SetOnsetThreshold(float threshold);
    float GetOnsetThresholdedNovelty() const;
    float GetOnsetNovelty() const;
    
    bool LowOnsetReceived();
    bool MidOnsetReceived();
    bool HighOnsetReceived();
    
    // Bands
    float * GetBandsEnergies() const;
    
private:
    int _sampleRate;
    int _bufferSize;
    
    essentia::standard::Algorithm *_lowPass;
    essentia::standard::Algorithm *_midPass;
    essentia::standard::Algorithm *_highPass;
    
    ofxAubioOnset _lowOnset;
    ofxAubioOnset _midOnset;
    ofxAubioOnset _highOnset;
    ofxAubioBeat _beat;
    ofxAubioMelBands _bands;
    
    vector<Real> _inputBuffer;
    vector<Real> _lowPassBuffer;
    vector<Real> _midPassBuffer;
    vector<Real> _highPassBuffer;
};

#endif
