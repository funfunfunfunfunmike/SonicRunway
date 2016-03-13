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
#include "AudioUI.hpp"
#include "Model.hpp"
#include "Artnet.hpp"
#include "Previs.hpp"

class SrPattern;

///
/// Main app.
/// Owns the audio buffer, patterns, etc.
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
    SrModel _model;
    SrAudio _audio;
    SrAudioUI _audioUI;
    SrPrevis _previs;
    SrArtnet _artnet;
    
    std::vector<SrPattern *> _patterns;
};

#endif
