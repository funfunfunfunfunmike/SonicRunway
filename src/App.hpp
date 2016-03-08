//
//  App.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/13/16.
//
//

#ifndef SR_APP_HPP
#define SR_APP_HPP

#include <stdio.h>

#include "Audio.hpp"
#include "FftBuffer.hpp"
#include "AudioUI.hpp"
#include "Model.hpp"
#include "Artnet.hpp"
#include "Previs.hpp"

class SrPattern;

///
/// Main app.  Much like ofApp, but with constructor/destructor
/// instead of setup/exit.
///
class SrApp {
public:
    SrApp();
    ~SrApp();
    
    void Update();
    void Draw();
    void AudioIn(float * input, int bufferSize, int nChannels);
    void AudioOut(float * output, int buferSize, int nChannels);
    
private:
    int _sampleRate;
    int _bufferSize;
    int _numChannels;
    int _framesPerSecond;
    
    SrModel _model;
    SrAudio _audio;
    SrFftBuffer _fftBuffer;
    SrAudioUI _audioUI;
    SrPrevis _previs;
    SrArtnet _artnet;
    
    std::vector<SrPattern *> _patterns;
};

#endif
