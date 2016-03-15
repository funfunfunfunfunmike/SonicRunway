//
//  BeatDetect.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/14/16.
//
//

#ifndef SR_BEAT_HISTORY_HPP
#define SR_BEAT_HISTORY_HPP

#include "EventHistory.hpp"
#include "ofxAubioBeat.h"

//
// SrBeatHistory - an SrEventHistory that records beat detection and BPM.
//
class SrBeatHistory : public SrEventHistory {
public:
    SrBeatHistory(SrModel * model);
    virtual ~SrBeatHistory();
    
    void AudioIn(float * input, int bufferSize, int nChannels);
    
    const SrFloatBuffer & GetBpm() const;
    
private:
    SrFloatBuffer _bpm;
    
    ofxAubioBeat _beat;
};

#endif 
