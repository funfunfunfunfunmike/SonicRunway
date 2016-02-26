//
//  Artnet.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/14/16.
//
//

#include "Artnet.hpp"

SrArtnet::SrArtnet()
{
    _artnet.setup("192.168.0.1");
    _artnet.verbose = true;
    
    
    /*
    _artnet.init("192.168.0.1", true);
    _artnet.setNodeType(ARTNET_TYPE_SERVER);
    _artnet.setPortType(1, ARTNET_PORT_ENABLE_OUTPUT, ARTNET_DATA_DMX);
    _artnet.start();
    */
}

void
SrArtnet::UpdateLights()
{
    
    /*
    const int len = 512;
    ofxArtNetDmxData dmxData(len);
    uint8_t data[len];
    
    for (int i=0; i<len; i++) {
        data[i] = 200;
    }
    
    _artnet.sendDmxRaw(1, data, len);
     */
}

SrArtnet::~SrArtnet()
{
    /*
    _artnet.stop();
    _artnet.close();
     */
}