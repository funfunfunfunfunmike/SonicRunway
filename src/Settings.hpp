//
//  Settings.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/10/16.
//
//

#ifndef _SR_SETTINGS_HPP
#define _SR_SETTINGS_HPP

#include <stdio.h>

///
/// Global settings for the app.
///
class SrSettings {
public:
    void Setup();
    void Update();
    void Exit();
    
    int GetNumStations() const;
    int GetLightsPerStation() const;
    
    float GetRunwayLength() const; // in feet
    float GetSpeedOfSound() const; // in feet per second
    
    float ComputeDelayPerStation() const; // in seconds
    
private:
    int _numStations;
    int _lightsPerStation;
    float _runwayLength;
    float _speedOfSound;
    
};

#endif
