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
    SrPattern(name, model, audio),
    _hueParam(0.0),
    _numStripesParam(6),
    _spinSpeedParam(1000.0), // revolutions per second
    _hueBuffer(model, SrFrequencyOncePerUpdate),
    _angleBuffer(model, SrFrequencyOncePerUpdate),
    _numStripesBuffer(model, SrFrequencyOncePerUpdate),
    _currentAngle(0.0) // degrees
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
SrStripesPattern::_Update(const SrTime & now)
{
    // Push the current values of the parameters into the buffers.
    _hueBuffer.Push((float) _hueParam);
    _numStripesBuffer.Push((float) _numStripesParam);
    
    _currentAngle += _spinSpeedParam / GetModel()->GetFramesPerSecond();
    
    _angleBuffer.Push((float) _currentAngle);
}

void
SrStripesPattern::_Draw(const SrTime & now) const
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
        
        float t = fmod(angle, 360.0) / 360.0;
        int ledIndex = t * model->GetLightsPerStation();
        
        ofFloatColor c;
        int numDecay = 15;
        for(int j = 0; j < numDecay; j++) {
            float t = (float) j / numDecay;
            float thisHue = fmod(hue + t * 0.2, 1.0);
            c.setHsb(thisHue, 1.0, (1.0-t));
            ofSetColor(c);
            ofDrawRectangle(i, ledIndex + j, 1, 1);
        }
    }
}
