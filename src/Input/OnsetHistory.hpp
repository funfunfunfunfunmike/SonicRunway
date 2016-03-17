//
//  OnsetHistory.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/11/16.
//
//

#ifndef SR_ONSET_HISTORY_HPP
#define SR_ONSET_HISTORY_HPP

#include "EventHistory.hpp"
#include "ofxAubio.h"

//
// SrOnsetHistory - an SrEventHistory that records onset detections.
//
class SrOnsetHistory : public SrEventHistory {
public:
    SrOnsetHistory(SrModel *model);
    virtual ~SrOnsetHistory();
    
    void AudioIn(float * input, int bufferSize, int nChannels);
    void SetCurrentThreshold(float currentThreshold);
    
    // XXX possible multi-threading issues returning const refs
    // to data structures that may be updated in a different thread.
    // Since these all operate on fixed memory, I'm ignoring this
    // until it becomes a problem...
    const SrFloatBuffer & GetSecondsSinceOnset() const;
    const SrFloatBuffer & GetThreshold() const;
    const SrFloatBuffer & GetThresholdedNovelty() const;
    const SrFloatBuffer & GetNovelty() const;
    
private:
    void _OnOnsetEvent(float & time);
    
private:
    bool _gotOnset;
    float _currentThreshold;
    SrFloatBuffer _threshold;
    SrFloatBuffer _thresholdedNovelty;
    SrFloatBuffer _novelty;
    
    ofxAubioOnset _onset;
};

#endif