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

class SrSettings;
class SrLightArray;
class SrCues;

///
/// A pattern that renders 'onset' cues to the lightArray,
/// streaming out at the speed of sound, with some decay.
///
class SrOnsetPattern {
public:
    SrOnsetPattern(SrSettings * settings,
                   SrLightArray * lightArray,
                   SrCues * cues);
    ~SrOnsetPattern();
    
    void Update(const SrTime & now);
    
private:
    SrSettings *_settings;
    SrLightArray *_lightArray;
    SrCues *_cues;
    
};

#endif
