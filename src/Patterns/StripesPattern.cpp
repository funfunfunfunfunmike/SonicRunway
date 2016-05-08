//
//  StripesPattern.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/22/16.
//
//

#include "StripesPattern.hpp"

SrStripesPattern::SrStripesPattern(const std::string & name,
                                   SrModel * model, SrAudio * audio) :
    SrScrollingPattern(name, model, audio),
    _hueParam(0.0),
    _numStripesParam(6),
    _spinSpeedParam(1000.0), // revolutions per second
    _angle(0.0) // degrees
{
    _hueParam.setName("Hue");
    _hueParam.setMin(0.0);
    _hueParam.setMax(1.0);
    _AddUIParameter(_hueParam);
    
    _numStripesParam.setName("Num Stripes");
    _numStripesParam.setMin(0);
    _numStripesParam.setMax(60);
    _AddUIParameter(_numStripesParam);
    
    _spinSpeedParam.setName("Spin Speed");
    _spinSpeedParam.setMin(-2000.0);
    _spinSpeedParam.setMax(2000.0);
    _AddUIParameter(_spinSpeedParam);
}

SrStripesPattern::~SrStripesPattern()
{
    
}

void
SrStripesPattern::_Update()
{
    SrScrollingPattern::_Update();
    
    _angle += _spinSpeedParam / GetModel()->ComputeFramesPerSecond();
}

void
SrStripesPattern::_DrawCurrentStation(std::vector<ofColor> * buffer) const
{
    const SrModel * model = GetModel();
    
    // Extract the values for each parameter for this station
    float enabled = GetEnabled()[0];
    if (not (bool) enabled) {
        return;
    }
    
    float hue = (float) _hueParam;
    
    float t = fmod(_angle, 360.0) / 360.0;
    int ledIndex = t * buffer->size();
    
    ofFloatColor c;
    int numDecay = (float) buffer->size() * 0.2;
    for(int i = 0; i < numDecay; i++) {
        float t = (float) i / numDecay;
        float thisHue = fmod(hue + t * 0.2, 1.0);
        c.setHsb(thisHue, 1.0, (1.0-t));
        
        int thisIndex = ledIndex + i;
        if (thisIndex >= buffer->size()) {
            continue;
        }
        
        (*buffer)[ledIndex + i] = c;
    }
}
