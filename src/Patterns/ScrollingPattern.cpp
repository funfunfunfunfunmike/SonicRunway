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
    int width = model->GetNumStations() * model->GetFramesPerStation();
    int height = model->GetLightsPerStation();
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
    
    // Draw the current station into a buffer
    std::vector<ofColor> currentColors(GetModel()->GetLightsPerStation());
    for(int i = 0; i < GetModel()->GetLightsPerStation(); i++) {
        currentColors[i] = ofColor::black;
    }
    
    if (GetEnabled()[0]) {
        _DrawCurrentStation(&currentColors);
    }
    
    // Copy the colors to our pixel cache
    for(int i = 0; i < GetModel()->GetLightsPerStation(); i++) {
        const ofColor & color = currentColors[i];
        _image.setColor(_index, i, color);
    }
}

void
SrScrollingPattern::_Draw() const
{
    const SrModel * model = GetModel();
    int numStations = model->GetNumStations();
    int lightsPerStation = model->GetLightsPerStation();
    
    for(int x = 0; x < numStations; x++) {
        for(int y = 0; y < lightsPerStation; y++) {
            int imageX = (x * model->GetFramesPerStation() + _index)
                      % (int) _image.getWidth();
           
            // XXX could be more efficient rendering fbo
            // instead of iterating here..
            ofSetColor(_image.getColor(imageX, y));
            ofDrawRectangle(x, y, 1, 1);
        }
    }
}
