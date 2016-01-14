//
//  Settings.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/10/16.
//
//

#include "Settings.hpp"

SrSettings::SrSettings() :
    _numStations(30),
    _lightsPerStation(16),
    _runwayLength(1000.0), // feet
    _speedOfSound(1126.0)  // feet per second
{
    
}

SrSettings::~SrSettings()
{
    
}

int
SrSettings::GetNumStations() const
{
    return _numStations;
}

int
SrSettings::GetLightsPerStation() const
{
    return _lightsPerStation;
}

float
SrSettings::GetRunwayLength() const
{
    return _runwayLength;
}

float
SrSettings::GetSpeedOfSound() const
{
    return _speedOfSound;
}

float
SrSettings::ComputeDelayPerStation() const
{
    return GetRunwayLength() / GetNumStations() / GetSpeedOfSound();
}