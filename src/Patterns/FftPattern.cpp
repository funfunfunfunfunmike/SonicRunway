//
//  FftPattern.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/4/16.
//
//

#include "FftPattern.hpp"
#include "Audio.hpp"
#include "Model.hpp"

SrFftPattern::SrFftPattern(const std::string & name,
                           SrModel * model, SrAudio * audio) :
    SrScrollingPattern(name, model, audio),
    _hueShiftParam(0.0)
{
    _hueShiftParam.setName("Hue");
    _hueShiftParam.setMin(0.0);
    _hueShiftParam.setMax(1.0);
    
    _AddUIParameter(_hueShiftParam);
}

SrFftPattern::~SrFftPattern()
{
    
}

void
SrFftPattern::_DrawCurrentGate(std::vector<ofColor> * buffer) const
{
    if (not GetEnabled()[0]) {
        return;
    }
    
    const SrModel * model = GetModel();
    int numLights = model->GetLightsPerGate();
    
    std::vector<float> ffts = GetAudio()->GetCurrentFftValues();
    
    if (ffts.empty()) {
        return;
    }
    
    float enabled = GetEnabled()[0];
    float hueShift = (float) _hueShiftParam;
    
    for(int i = 0; i < numLights; i++) {
        float t = (float) i / numLights;
        
        // Reduce t since we're mirroring below..
        t *= 0.7;
        
        int band = t * ffts.size() - 1;
        if (band >= ffts.size()) {
            band = ffts.size() - 1;
        }
        
        float fftValue = ffts[band];
       
        ofFloatColor c;
        float baseColor = 0.15 + hueShift;
        float hue = baseColor - 0.4 * (1.0 - fftValue);
        if (hue < 0.0) {
            hue += 1.0;
        }
       
        hue = fmod(hue, 1.0);
        c.setHsb(hue, 1.0, fftValue * 2.0);
        
        (*buffer)[i] += c;
        
        // mirror image
        (*buffer)[numLights - 1 - i] += c;
    }
}
