//
//  Artnet.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/14/16.
//
//

#ifndef SR_ARTNET_HPP
#define SR_ARTNET_HPP

#include <stdio.h>
#include "ofxArtnet.hpp"
#include "ofMain.h"
#include "LightArray.hpp"

class SrArtnet {
public:
    SrArtnet(const SrLightArray & lightArray);
    ~SrArtnet();
    
    void UpdateLights();
    
private:
    const SrLightArray & _lightArray;
    
    ofxArtnet _artnet;
    ofImage _testImage;
    ofFbo _fbo;
};

#endif
