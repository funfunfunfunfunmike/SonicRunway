//
//  ScrollingPattern.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 5/5/16.
//
//

#include "ScrollingPattern.hpp"

SrScrollingPattern::SrScrollingPattern(const std::string & name,
                                   SrModel * model, SrAudio * audio) :
    SrPattern(name, model, audio),
    _index(0)
{
    int width = model->GetNumGates() * model->GetFramesPerGate();
    int height = model->GetLightsPerGate();
    int numChannels = 4;
    
    _image.allocate(width, height, OF_IMAGE_COLOR_ALPHA);
    _image.setColor(ofColor::black);
}

SrScrollingPattern::~SrScrollingPattern()
{
    
}

void
SrScrollingPattern::_Update()
{
    _index--;
    if (_index < 0) {
        _index = (int) _image.getWidth() - 1;
    }
    
    // Draw the current gate into a buffer
    std::vector<ofColor> currentColors(GetModel()->GetLightsPerGate());
    for(int i = 0; i < GetModel()->GetLightsPerGate(); i++) {
        currentColors[i] = ofColor::black;
    }
    
    if (GetEnabled()[0]) {
        _DrawCurrentGate(&currentColors);
    }
    
    // Copy the colors to our pixel cache
    for(int i = 0; i < GetModel()->GetLightsPerGate(); i++) {
        const ofColor & color = currentColors[i];
        _image.setColor(_index, i, color);
    }
}

void
SrScrollingPattern::_Draw() const
{
    const SrModel * model = GetModel();
    int numGates = model->GetNumGates();
    int lightsPerGate = model->GetLightsPerGate();
    
    for(int x = 0; x < numGates; x++) {
        for(int y = 0; y < lightsPerGate; y++) {
            int imageX = (x * model->GetFramesPerGate() + _index)
                      % (int) _image.getWidth();
           
            // XXX could be more efficient rendering fbo
            // instead of iterating here..
            ofSetColor(_image.getColor(imageX, y));
            ofDrawRectangle(x, y, 1, 1);
        }
    }
}
