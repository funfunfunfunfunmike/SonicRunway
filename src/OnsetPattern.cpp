//
//  OnsetPattern.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/11/16.
//
//

#include "OnsetPattern.hpp"
#include "Model.hpp"
#include "LightArray.hpp"
#include "Cues.hpp"
#include "ofMain.h"

SrOnsetPattern::SrOnsetPattern(SrModel * model,
                               SrLightArray * lightArray,
                               const SrQueue & queue) :
    _model(model),
    _lightArray(lightArray),
    _queue(queue),
    _hue(100),
    _yMin(0.0),
    _yMax(1.0)
{
    
}

SrOnsetPattern::~SrOnsetPattern()
{
    
}

static float
_Clamp(float a, float min, float max)
{
    if (a < min) {
        a = min;
    }
    if (a > max) {
        a = max;
    }
    
    return a;
}

void
SrOnsetPattern::SetHue(float hue)
{
    _hue = hue;
}

void
SrOnsetPattern::SetYRange(float yMin, float yMax)
{
    _yMin = yMin;
    _yMax = yMax;
}

void
SrOnsetPattern::Update(const SrTime & now)
{
    float decayTime = 0.25; // seconds
    float maxBrightness = 0.7; /* [0,1] */
    
    // For each onset cue
    for (auto iter=_queue.begin(); iter != _queue.end(); iter++) {
        const SrCue & cue = *iter;
        
        float cueAge = cue.GetAge(now);
        
        // For each station
        for (int x = 0; x < _model->GetNumStations(); x++) {
           
            // Caclulate station delay.
            float stationDelay = _model->ComputeDelayPerStation() * x;
            float relativeAge = cueAge - stationDelay;
            
            // Bail if the sound hasn't gotten here yet.
            if (relativeAge < 0) {
                continue;
            }
            
            float factor = 1.0 - (relativeAge / decayTime);
            factor = _Clamp(factor, 0.0, 1.0);
            factor = pow(factor, 2);
            
            factor *= maxBrightness;
            
            float brightness = factor * 255.0;
            float saturation = (1.0 - factor) * 255.0;
            
            ofColor color;
            color.setHsb(_hue, saturation, brightness);
            
            // For each light in the station.
            int yMin = _yMin * _model->GetLightsPerStation();
            int yMax = _yMax * _model->GetLightsPerStation();
            for (int y = yMin; y < yMax; y++) {
                _lightArray->AddColor(x, y, color);
            }
        }
    }
}