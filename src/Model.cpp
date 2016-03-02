//
//  Model.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/10/16.
//
//

#include "Model.hpp"

SrModel::SrModel() :
    _numStations(30),
    _lightsPerStation(16),
    _runwayLength(1000.0), // feet
    _speedOfSound(1126.0)  // feet per second
{
    
}

SrModel::~SrModel()
{
    
}

int
SrModel::GetNumStations() const
{
    return _numStations;
}

int
SrModel::GetLightsPerStation() const
{
    return _lightsPerStation;
}

float
SrModel::GetRunwayLength() const
{
    return _runwayLength;
}

float
SrModel::GetSpeedOfSound() const
{
    return _speedOfSound;
}

float
SrModel::ComputeDelayPerStation() const
{
    return GetRunwayLength() / GetNumStations() / GetSpeedOfSound();
}
