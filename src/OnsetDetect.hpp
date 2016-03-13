//
//  OnsetDetect.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/11/16.
//
//

#ifndef SR_ONSET_DETECT_HPP
#define SR_ONSET_DETECT_HPP

#include <stdio.h>
#include "Buffer.hpp"
#include "ofxAubio.h"
#include "Types.hpp"

class SrOnsetDetect {
public:
    SrOnsetDetect(SrModel *model);
    ~SrOnsetDetect();
    
    void AudioIn(float * input, int bufferSize, int nChannels);
    void SetCurrentThreshold(float currentThreshold);
    
    SrTime GetTimeOfLastOnset() const;
    
    // XXX possible multi-threading issues returning const refs
    // to data structures that may be updated in a different thread.
    // Since these all operate on fixed memory, I'm ignoring this
    // until it becomes a problem...
    const SrFloatBuffer & GetSecondsSinceOnset() const;
    const SrFloatBuffer & GetThreshold() const;
    const SrFloatBuffer & GetThresholdedNovelty() const;
    const SrFloatBuffer & GetNovelty() const;
    
private:
    float _currentThreshold;
    SrFloatBuffer _secondsSinceOnset;
    SrFloatBuffer _threshold;
    SrFloatBuffer _thresholdedNovelty;
    SrFloatBuffer _novelty;
    SrTime _timeOfLastOnset;
    
    ofxAubioOnset _onset;
};

#endif