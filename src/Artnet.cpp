//
//  Artnet.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/14/16.
//
//

#include "Artnet.hpp"
#include "Model.hpp"

SrArtnet::SrArtnet(SrModel * model) :
    _model(model)
{
    _artnet.setup("192.168.0.1");
    _artnet.verbose = false;
}

void
SrArtnet::UpdateLights()
{
    if (_artnet.status != NODES_FOUND) {
        return;
    }
    
    std::vector<unsigned char> data(512 * 3);
    
    const ofFloatPixels & pixels = _model->GetFloatPixels();
    
    for (int i=0; i < _model->GetLightsPerGate(); i++) {
        ofFloatColor color = pixels.getColor(0, i);
        
        color.setHsb(color.getHue(), color.getSaturation(),
                     color.getBrightness() * color.getBrightness());
        data[i*3] = color[0] * 255;
        data[i*3 + 1] = color[1] * 255;
        data[i*3 + 2] = color[2] * 255;
    }
    
    /*
    for(int i=0; i < _model->GetNumGates(); i++) {
        int y = _model->GetLightsPerGate() / 3.0;
        ofFloatColor color = pixels.getColor(i, y);
        
        // XXX hacking gamma correction by squaring the
        // brightness.  Clearly there is a more accurate way...
        color.setHsb(color.getHue(), color.getSaturation(),
                     color.getBrightness() * color.getBrightness());
        data[i*3] = color[0] * 255;
        data[i*3 + 1] = color[1] * 255;
        data[i*3 + 2] = color[2] * 255;
    }
     */
    
    //list nodes for sending
    //with subnet / universe
    //    artnet.sendDmx("10.0.0.149", 0xf, 0xf, _testImage.getPixels(), 512);
    
    _artnet.sendDmx("192.168.0.50", &data[0], 512);
    
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
