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
#include "OnsetDetect.hpp"

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
    
    const SrOnsetDetect & GetLowOnset() const;
    const SrFloatBuffer & GetBpm() const;
    const vector<SrFloatBuffer> & GetFfts() const;
    
    void AudioIn(float * input, int bufferSize, int nChannels);
    void AudioOut(float * output, int bufferSize, int nChannels);
    
    std::vector<float> GetCurrentFftValues() const;
    
private:
    SrModel * _model;
    SrOnsetDetect _lowOnsetDetect;
    SrFloatBuffer _bpm;
    vector<SrFloatBuffer> _ffts;
    
    essentia::standard::Algorithm *_bandPass;
    
    ofxAubioBeat _beat;
    ofxAubioMelBands _bands;
    
    vector<Real> _inputBuffer;
    vector<Real> _bandPassBuffer;
};

#endif
