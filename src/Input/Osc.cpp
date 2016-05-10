//
//  Osc.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 5/9/16.
//
//

#include "Osc.hpp"

SrOsc::SrOsc()
{
    printf("constructed osc");
    
    _receiver.setup(8000);
}

void
SrOsc::Update()
{
    while (_receiver.hasWaitingMessages()) {
        ofxOscMessage m;
        _receiver.getNextMessage(&m);
        
        printf("received message!\n");
    }
    
}