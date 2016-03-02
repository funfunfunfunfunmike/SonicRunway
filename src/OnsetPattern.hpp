//
//  OnsetPattern.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/11/16.
//
//

#ifndef SR_ONSET_PATTERN_HPP
#define SR_ONSET_PATTERN_HPP

#include <stdio.h>

#include "Types.hpp"
#include "Cues.hpp"

class SrModel;
class SrLightArray;

///
/// A pattern that renders 'onset' cues to the lightArray,
/// streaming out at the speed of sound, with some decay.
///
class SrOnsetPattern {
public:
    SrOnsetPattern(SrModel * model,
                   const SrQueue & queue);
    ~SrOnsetPattern();
    
    void Draw(const SrTime & now);
    
    void SetHue(float hue);
    void SetYRange(float yMin, float yMax);
    
private:
    SrModel *_model;
    const SrQueue & _queue;
    float _hue;
    float _yMin, _yMax;
};

#endif
