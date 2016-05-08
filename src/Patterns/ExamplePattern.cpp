//
//  ExamplePattern.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/17/16.
//
//

#include "ExamplePattern.hpp"

SrExamplePattern::SrExamplePattern(const std::string & name,
                                 SrModel * model, SrAudio * audio) :
    SrScrollingPattern(name, model, audio),
    _hueParam(0.0),
    _angleParam(135.0)
{
    _hueParam.setName("Hue");
    _hueParam.setMin(0.0);
    _hueParam.setMax(1.0);
    _AddUIParameter(_hueParam);
    
    _angleParam.setName("Angle");
    _angleParam.setMin(0.0);
    _angleParam.setMax(360.0);
    _AddUIParameter(_angleParam);
}

SrExamplePattern::~SrExamplePattern()
{
    
}

void
SrExamplePattern::_DrawCurrentStation(std::vector<ofColor> * buffer) const
{
    float hue = _hueParam;
    float angle = _angleParam;
    
    float t = angle / 270.0;
    int index = t * buffer->size();
    
    // Make sure we don't access outside the buffer when t == 1
    index = index % buffer->size();
    
    ofFloatColor c;
    c.setHsb(hue, 1.0, 0.8);
    
    (*buffer)[index] = c;
}
