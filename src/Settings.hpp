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
    SrSettings();
    ~SrSettings();
    
    void Update();
    
    int GetNumStations() const;
    int GetLightsPerStation() const;
    
    float GetRunwayLength() const; // in feet
    float GetSpeedOfSound() const; // in feet per second
    
    float ComputeDelayPerStation() const; // in seconds
    
    int GetSampleRate() const;
    int GetBufferSize() const;
    int GetNumChannels() const;
    
private:
    int _numStations;
    int _lightsPerStation;
    float _runwayLength;
    float _speedOfSound;
    int _sampleRate;
    int _bufferSize;
    int _numChannels;
};

#endif
