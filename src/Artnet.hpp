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
#include "Model.hpp"

class SrArtnet {
public:
    SrArtnet(const SrModel & model);
    ~SrArtnet();
    
    void UpdateLights();
    
private:
    const SrModel & _model;
    
    ofxArtnet _artnet;
    ofImage _testImage;
    ofFbo _fbo;
};

#endif
