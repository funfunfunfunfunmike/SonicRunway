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

class SrArtnet {
public:
    SrArtnet();
    ~SrArtnet();
    
    void UpdateLights();
    
private:
    ofxArtnet _artnet;
};

#endif
