//
//  Osc.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 5/9/16.
//
//

#ifndef SR_OSC_HPP
#define SR_OSC_HPP

#include <stdio.h>
#include "ofxOsc.h"

class SrOsc {
public:
    SrOsc();
    
    void Update();
    
private:
    ofxOscReceiver _receiver;
};


#endif /* Osc_hpp */
