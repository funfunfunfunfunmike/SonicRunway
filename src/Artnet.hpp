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

class SrModel;

//
// Artnet output - translates the current buffer into Artnet/DMX signals
// to update the LED colors.
//
class SrArtnet {
public:
    SrArtnet(SrModel * model);
    ~SrArtnet();
    
    void UpdateLights();
    
private:
    SrModel * _model;
    
    ofxArtnet _artnet;
    ofImage _testImage;
    ofFbo _fbo;
};

#endif
