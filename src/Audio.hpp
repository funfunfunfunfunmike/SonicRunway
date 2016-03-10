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
#include "Buffer.hpp"

#include "ofMain.h"

#include <essentia/essentia.h>
#include <essentia/algorithmfactory.h>

class ofApp;
class SrModel;

// XXX this should be defined in essentia somewhere..
typedef float Real;

///
/// SrAudio - Audio input and processing.
///
class SrAudio {
public:
    SrAudio(SrModel * model);
    ~SrAudio();
    
    void AudioIn(float * input, int bufferSize, int nChannels);
    void AudioOut(float * output, int bufferSize, int nChannels);
    
    // XXX should create subclasses to hold parameters..
    enum Event {
        Beat,
        LowOnset,
        Thump
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
    
    // Buffers
    const vector<SrFloatBuffer> & GetFftBuffers() const { return _fftBuffers; }
    const SrFloatBuffer & GetLowOnsetBuffer() const { return _lowOnsetBuffer; }
    
private:
    SrModel * _model;
    
    int _numMelBands;
    
    uint64_t _lastLowOnsetTime;
    uint64_t _lastBeatTime;
    uint64_t _lastThumpTime;
    
    essentia::standard::Algorithm *_bandPass;
    
    ofxAubioOnset _lowOnset;
    ofxAubioBeat _beat;
    ofxAubioMelBands _bands;
    
    vector<Real> _inputBuffer;
    vector<Real> _bandPassBuffer;
    
    std::vector<Event> _currentEvents;
    
    vector<SrFloatBuffer> _fftBuffers;
    SrFloatBuffer _lowOnsetBuffer;
};

#endif
