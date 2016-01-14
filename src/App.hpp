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
#include "Settings.hpp"
#include "Cues.hpp"
#include "LightArray.hpp"
#include "GridDisplay.hpp"
#include "OnsetPattern.hpp"
#include "Artnet.hpp"

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
    void AudioIn(float * input, int bufferSize,
                 int nChannels);
    
private:
    SrSettings _settings;
    SrCues _cues;
    SrLightArray _lightArray;
    SrAudio _audio;
    SrAudioUI _audioUI;
    SrOnsetPattern _onsetPattern;
    SrGridDisplay _gridDisplay;
    SrArtnet _artnet;
};

#endif
