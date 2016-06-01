//
//  BeatPattern.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 5/7/16.
//
//

#include "BeatPattern.hpp"
#include "Audio.hpp"
#include "BeatHistory.hpp"

SrBeatPattern::SrBeatPattern(const std::string & name,
                                   SrModel * model, SrAudio * audio) :
    SrScrollingPattern(name, model, audio),
    _hueParam(0.5),
    _decayTimeParam(0.25),
    _spinSpeedParam(0.25),
    _hueSpeedParam(0.0),
    _spinOffset(0.2),
    _hueOffset(0.0)
{
    _hueParam.setName("Hue");
    _hueParam.setMin(0.0);
    _hueParam.setMax(1.0);
    _AddUIParameter(_hueParam);
    
    _decayTimeParam.setName("DecayTime");
    _decayTimeParam.setMin(0.0);
    _decayTimeParam.setMax(1.0);
    _AddUIParameter(_decayTimeParam);
    
    _spinSpeedParam.setName("SpinSpeed");
    _spinSpeedParam.setMin(-3.0);
    _spinSpeedParam.setMax(3.0);
    _AddUIParameter(_spinSpeedParam);
    
    _hueSpeedParam.setName("HueSpeed");
    _hueSpeedParam.setMin(-0.1);
    _hueSpeedParam.setMax(0.1);
    //_AddUIParameter(_hueSpeedParam);
}

SrBeatPattern::~SrBeatPattern()
{
    
}

void
SrBeatPattern::_Update()
{
    SrScrollingPattern::_Update();
    
    _spinOffset += (float) _spinSpeedParam;
    _hueOffset += (float) _hueSpeedParam;
}

void
SrBeatPattern::_DrawCurrentGate(std::vector<ofColor> * buffer) const
{
    //float hue = fmod(fabs(_hueParam + _hueOffset), 1.0);
    float hue = (float) _hueParam;
    
    float timeSinceBeat =
        GetAudio()->GetBeatHistory().GetSecondsSinceLastEvent()[0];
    
    float onsetDecayTime = (float) _decayTimeParam;
    
    float onsetAmount = 1.0 - timeSinceBeat / onsetDecayTime;
    
    if (onsetAmount < 0.0) {
        return;
    }
    
    float onsetMult = onsetAmount;
    
    // Force full onsetAmount if we're less than one full gate behind.
    if (timeSinceBeat < GetModel()->ComputeDelayPerGate()) {
        onsetMult = 1.0;
    }
    
    onsetMult *= onsetMult;
    
    ofFloatColor c;
    c.setHsb(hue, 1.0, onsetMult);
    for(int i = 0; i < buffer->size(); i++) {
        
        int lightsPerTrailer = buffer->size() / 10;
        
        // XXX this is bad b/c it isn't normalized to number of lights.
        int iNumerator = i + _spinOffset;
        
        float trailDiminish = (float) (iNumerator % lightsPerTrailer) / lightsPerTrailer;
        trailDiminish = onsetAmount * 1.0 + (1.0 - onsetAmount) * trailDiminish;
        trailDiminish *= trailDiminish;
       
        float thisMult = onsetMult * trailDiminish;
        float thisHue = hue + 0.3 * (1.0 - thisMult);
        if (thisHue < 0.0) {
            thisHue += 1.0;
        }
        thisHue = fmod(thisHue, 1.0);
       
        ofFloatColor thisC;
        thisC.setHsb(thisHue, 1.0, thisMult);
        
        (*buffer)[i] = thisC;
    }
}
