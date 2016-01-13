//
//  OnsetPattern.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/11/16.
//
//

#include "OnsetPattern.hpp"
#include "Settings.hpp"
#include "LightArray.hpp"
#include "Cues.hpp"
#include "ofMain.h"

void
SrOnsetPattern::Setup(SrSettings * settings,
                     SrLightArray * lightArray,
                     SrCues * cues)
{
    _settings = settings;
    _lightArray = lightArray;
    _cues = cues;
}

void
SrOnsetPattern::Exit()
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
SrOnsetPattern::Update(const SrTime & now)
{
    float hue = 100.0; // [0,255]
    float decayTime = 0.25; // seconds
    float maxBrightness = 0.7; /* [0,1] */
    
    // For each onset cue
    const SrQueue & onsetQueue = _cues->GetOnsetQueue();
    for (auto iter=onsetQueue.begin(); iter != onsetQueue.end(); iter++) {
        const SrCue & cue = *iter;
        
        float cueAge = cue.GetAge(now);
        
        // For each station
        for (int x = 0; x < _settings->GetNumStations(); x++) {
           
            // Caclulate station delay.
            float stationDelay = _settings->ComputeDelayPerStation() * x;
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
            color.setHsb(hue, saturation, brightness);
            
            // For each light in the station.
            for (int y = 0; y < _settings->GetLightsPerStation(); y++) {
                _lightArray->AddColor(x, y, color);
            }
        }
    }
}