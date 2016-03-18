//
//  StripePattern.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/17/16.
//
//

#include "StripePattern.hpp"

SrStripePattern::SrStripePattern(const std::string & name,
                                 SrModel * model, SrAudio * audio) :
    SrPattern(name, model, audio),
    _hueParam(0.0),
    _angleParam(135.0),
    _hueBuffer(model, SrFrequencyOncePerUpdate),
    _angleBuffer(model, SrFrequencyOncePerUpdate)
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

SrStripePattern::~SrStripePattern()
{
    
}

void
SrStripePattern::_Update(const SrTime & now)
{
    // Push the current values of the parameters into the buffers.
    _hueBuffer.Push((float) _hueParam);
    _angleBuffer.Push((float) _angleParam);
}

void
SrStripePattern::_Draw(const SrTime & now) const
{
    const SrModel * model = GetModel();
    int numStations = model->GetNumStations();
    
    for(int i = 0; i < numStations; i++) {
        
        // Extract the values for each parameter for this station
        float enabled = GetEnabled().ComputeValueAtStation(i);
        if (not (bool) enabled) {
            continue;
        }
        
        float hue = _hueBuffer.ComputeValueAtStation(i);
        float angle = _angleBuffer.ComputeValueAtStation(i);
        
        float t = angle / 270.0;
        int ledIndex = t * model->GetLightsPerStation();
        
        ofFloatColor c;
        c.setHsb(hue, 1.0, 0.8);
       
        ofSetColor(c);
        ofDrawRectangle(i, ledIndex, 1, 1);
    }
}
