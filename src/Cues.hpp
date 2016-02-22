//
//  Cues.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/11/16.
//
//

#ifndef SR_CUES_HPP
#define SR_CUES_HPP

#include "Types.hpp"

#include <stdio.h>
#include <chrono>
#include <deque>

class SrAudio;

///
/// SrCue - A musical cue in the audio stream.
///
class SrCue {
public:
    SrCue(const SrTime &time);
    
    SrTime GetTime() const;
    float GetAge(const SrTime & now) const;
private:
    SrTime _time;
    
};

typedef std::deque<SrCue> SrQueue;

///
/// SrCues - A container to hold all the recent SrCues that were
/// generated from the audio stream.  This is passed to patterns
/// as the input for music visualization.
///
class SrCues {
   
public:
    SrCues(SrAudio *audio);
    ~SrCues();
    
    void Update(const SrTime & now);
    
    const SrQueue & GetBeatQueue() const;
    const SrQueue & GetLowOnsetQueue() const;
    const SrQueue & GetMidOnsetQueue() const;
    const SrQueue & GetHighOnsetQueue() const;
    
private:
    void _RemoveOutdatedCues(SrQueue *queue,
                             const SrTime &expiration);
    
private:
    SrAudio *_audio;
    SrTime _initialTime;
    
    SrQueue _beatQueue;
    SrQueue _lowOnsetQueue;
    SrQueue _midOnsetQueue;
    SrQueue _highOnsetQueue;
};

#endif /* Cues_hpp */
