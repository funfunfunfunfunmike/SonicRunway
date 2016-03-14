//
//  EventHistory.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/14/16.
//
//

#include "EventHistory.hpp"
#include "Model.hpp"

SrEventHistory::SrEventHistory(SrModel * model,
                               SrFrequency pushFrequency) :
    _secondsSinceLastEvent(model, pushFrequency)
{
    
}

SrEventHistory::~SrEventHistory()
{
    
}

SrTime
SrEventHistory::GetTimeOfLastEvent() const
{
    return _timeOfLastEvent;
}

const SrFloatBuffer &
SrEventHistory::GetSecondsSinceLastEvent() const
{
    return _secondsSinceLastEvent;
}

void
SrEventHistory::_Push(bool isEvent)
{
    SrTime now = std::chrono::system_clock::now();
    if (isEvent) {
        _timeOfLastEvent = now;
    }
    
    float secondsSinceLastEvent =
    SrFloatDuration(now - _timeOfLastEvent).count();
    _secondsSinceLastEvent.Push(secondsSinceLastEvent);
}
