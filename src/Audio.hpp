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
#include "Types.hpp"
#include "ofMain.h"

#include <essentia/essentia.h>
#include <essentia/algorithmfactory.h>

class ofApp;

// XXX this should be defined in essentia somewhere..
typedef float Real;

///
/// SrAudio - Audio input and processing.
///
class SrAudio {
public:
    SrAudio(int sampleSize, int bufferSize);
    ~SrAudio();
    
    void AudioIn(float * input, int bufferSize, int nChannels);
    void AudioOut(float * output, int bufferSize, int nChannels);
    
    // XXX should create subclasses to hold parameters..
    enum Event {
        Beat,
        LowOnset
    };
    
    void UpdateEvents(const SrTime &now);
    
    const std::vector<Event> & GetCurrentEvents() const;
    
    // Beat
    float GetBPM() const;
    
    // Onset
    float GetOnsetThreshold() const;
    void SetOnsetThreshold(float threshold);
    float GetOnsetThresholdedNovelty() const;
    float GetOnsetNovelty() const;
    
    // Bands
    int GetNumMelBands() const;
    float * GetBandsEnergies() const;
    
private:
    int _sampleRate;
    int _bufferSize;
    int _numMelBands;
    
    essentia::standard::Algorithm *_bandPass;
    
    ofxAubioOnset _lowOnset;
    ofxAubioBeat _beat;
    ofxAubioMelBands _bands;
    
    vector<Real> _inputBuffer;
    vector<Real> _bandPassBuffer;
    
    std::vector<Event> _currentEvents;
};

#endif
