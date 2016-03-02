//
//  Artnet.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/14/16.
//
//

#include "Artnet.hpp"

SrArtnet::SrArtnet(const SrModel & model) :
    _model(model)
{
    _artnet.setup("192.168.0.1");
    _artnet.verbose = true;
    
    _fbo.allocate(512, 1, GL_RGB);
}

void
SrArtnet::UpdateLights()
{
    if (_artnet.status != NODES_FOUND) {
        return;
    }
    
    //create send buffer by ofFbo
    {
        _fbo.begin();
        ofClear(0);
       
        /*
        float colorR = (sin(ofGetElapsedTimeMillis() / 1000.f) / 2.f + 0.5f) * 255.f;
        float colorG = (sin((ofGetElapsedTimeMillis() / 1000.f) + PI / 3.f) / 2.f + 0.5f) * 255.f;
        float colorB = (sin((ofGetElapsedTimeMillis() / 1000.f)  + PI * 2.f / 3.f) / 2.f + 0.5f) * 255.f;
        ofSetColor((int)colorR, (int)colorG, (int)colorB);
         */
        
        /*
        ofSetColor(_lightArray.GetColor(0,0));
         */
        ofRect(0, 0, 512, 1);
        _fbo.end();
        _fbo.readToPixels(_testImage.getPixelsRef());
    }
    
    //list nodes for sending
    //with subnet / universe
    //    artnet.sendDmx("10.0.0.149", 0xf, 0xf, _testImage.getPixels(), 512);
    _artnet.sendDmx("192.168.0.50", _testImage.getPixels(), 512);
    
}

SrArtnet::~SrArtnet()
{
    // XXX cleanup fbo??
    // Stop artnet?
    
    /*
    _artnet.stop();
    _artnet.close();
     */
}