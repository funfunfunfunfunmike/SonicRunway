//
//  Types.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/11/16.
//
//

#ifndef SR_TYPES_H
#define SR_TYPES_H

#include <stdio.h>

#include <chrono>

// XXX this is kinda confusing.  Replace with seconds/milliseconds?
// Not sure about precision issues with elapsed time and what happens
// when time values roll over..
typedef std::chrono::time_point<std::chrono::system_clock> SrTime;
typedef std::chrono::seconds SrSeconds;
typedef std::chrono::duration<float> SrFloatDuration;

#endif
