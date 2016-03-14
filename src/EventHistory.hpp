//
//  EventHistory.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/14/16.
//
//

#ifndef SR_EVENT_HISTORY_HPP
#define SR_EVENT_HISTORY_HPP

#include <stdio.h>
#include "Buffer.hpp"
#include "Types.hpp"

//
// Base class for recording a history of some kind of boolean event,
// such as a beat, onset, or trigger of some kind.
//
// Subclasses should specify an update frequency, and call '_Push'
// once per cycle, specifying if the event has occurred.  Clients
// can then query the time since the last event, or get a buffer
// that contains samples recording the time since the last event
// occurred.  This allows patterns to query how long it has been
// since a given event happened, relative to a particular station.
//
class SrEventHistory {
public:
    SrEventHistory(SrModel * model, SrFrequency pushFrequency);
    virtual ~SrEventHistory();
   
    SrTime GetTimeOfLastEvent() const;
    
    const SrFloatBuffer & GetSecondsSinceLastEvent() const;
    
protected:
    // Subclasses must call this at the given pushFrequency
    void _Push(bool isEvent);
    
private:
    SrFloatBuffer _secondsSinceLastEvent;
    SrTime _timeOfLastEvent;
};

#endif
