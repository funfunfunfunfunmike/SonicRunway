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

class SrSettings;
class SrLightArray;

///
/// A pattern that renders 'onset' cues to the lightArray,
/// streaming out at the speed of sound, with some decay.
///
class SrOnsetPattern {
public:
    SrOnsetPattern(SrSettings * settings,
                   SrLightArray * lightArray,
                   const SrQueue & queue);
    ~SrOnsetPattern();
    
    void Update(const SrTime & now);
    
    void SetHue(float hue);
    void SetYRange(float yMin, float yMax);
    
private:
    SrSettings *_settings;
    SrLightArray *_lightArray;
    const SrQueue & _queue;
    float _hue;
    float _yMin, _yMax;
};

#endif
