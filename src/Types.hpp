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

typedef std::chrono::time_point<std::chrono::system_clock> SrTime;
typedef std::chrono::seconds SrSeconds;
typedef std::chrono::duration<float> SrFloatDuration;

#endif
