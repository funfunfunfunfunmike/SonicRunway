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
#include "OnsetHistory.hpp"
#include "BeatHistory.hpp"

#include "ofMain.h"

#include <essentia/essentia.h>
#include <essentia/algorithmfactory.h>

class ofApp;
class SrModel;

// XXX this should be defined in essentia somewhere..
typedef float Real;

//
// SrAudio - Audio input and processing.
//
class SrAudio {
public:
    SrAudio(SrModel * model);
    ~SrAudio();
    
    const SrOnsetHistory & GetLowOnsetHistory() const;
    const SrBeatHistory & GetBeatHistory() const;
    const vector<SrFloatBuffer> & GetFfts() const;
    
    void AudioIn(float * input, int bufferSize, int nChannels);
    //void AudioOut(float * output, int bufferSize, int nChannels) const;
    void AudioOutDelayed(float * output, int bufferSize, int nChannels,
                         float delayInSeconds) const;
    
    void SetOutputAudioDelayed(bool sendAudioOut);
    
    typedef vector<vector<float> > AudioVecBuffer;
    const AudioVecBuffer & GetFullAudioBuffer(float delayInSeconds) const;
    
    std::vector<float> GetCurrentFftValues() const;
    
private:
    SrModel * _model;
    SrOnsetHistory _lowOnsetHistory;
    SrBeatHistory _beatHistory;
    vector<SrFloatBuffer> _ffts;
    int _fullAudioBufferIndex;
    
    AudioVecBuffer _fullAudioBuffer;
    
    essentia::standard::Algorithm *_bandPass;
    
    bool _outputDelayed;
    
    ofxAubioMelBands _bands;
    
    vector<Real> _inputBuffer;
    vector<Real> _bandPassBuffer;
};

#endif
