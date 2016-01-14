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
#include "artnet.h"

class SrArtnet {
public:
    SrArtnet();
    ~SrArtnet();
    
private:
    artnet_node _artnetNode;
    
};

#endif
