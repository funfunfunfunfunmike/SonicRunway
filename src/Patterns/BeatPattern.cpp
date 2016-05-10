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
    _hueParam(0.5)
{
    _hueParam.setName("Hue");
    _hueParam.setMin(0.0);
    _hueParam.setMax(1.0);
    _AddUIParameter(_hueParam);
}

SrBeatPattern::~SrBeatPattern()
{
    
}

void
SrBeatPattern::_DrawCurrentGate(std::vector<ofColor> * buffer) const
{
    float hue = _hueParam;
    
    float timeSinceBeat =
        GetAudio()->GetBeatHistory().GetSecondsSinceLastEvent()[0];
    
    float onsetDecayTime = 0.25;
    
    float onsetAmount = 1.0 - timeSinceBeat / onsetDecayTime;
    
    if (onsetAmount < 0.0) {
        return;
    }
    
    // Force full onsetAmount if we're less than one full gate behind.
    if (timeSinceBeat < GetModel()->ComputeDelayPerGate()) {
        onsetAmount = 1.0;
    }
    
    onsetAmount *= onsetAmount;
    
    printf("onset amt %f\n", onsetAmount);
    
    ofFloatColor c;
    c.setHsb(hue, 1.0, onsetAmount);
    for(int i = 0; i < buffer->size(); i++) {
        (*buffer)[i] = c;
    }
}
