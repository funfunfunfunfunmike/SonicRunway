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
    char *ip_addr = NULL;
    
    uint8_t subnet_addr = 0;
    uint8_t port_addr = 1;
    
    printf("creating artnet node\n");
    _artnetNode = artnet_new(ip_addr, 1);
}

SrArtnet::~SrArtnet()
{
    printf("deleting artnet node\n");
    artnet_stop(_artnetNode);
    artnet_destroy(_artnetNode);
}