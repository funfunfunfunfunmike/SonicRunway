//
//  Model.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/10/16.
//
//

#ifndef _SR_MODEL_HPP
#define _SR_MODEL_HPP

#include <stdio.h>
#include "ofMain.h"

///
/// Model class for the app.  Holds global settings and
/// the main frame buffer that store the color of all the lights.
///
class SrModel {
public:
    SrModel();
    ~SrModel();
    
    void Update();
    
    int GetNumStations() const;
    int GetLightsPerStation() const;
    
    float GetRunwayLength() const; // in feet
    float GetSpeedOfSound() const; // in feet per second
    float GetArchLength() const;  // in feet
    float GetFramesPerSecond() const;
    
    float ComputeDelayPerStation() const; // in seconds
    
    
    
    void Clear();
    void BeginDrawing();
    void EndDrawing();
    
    const ofFloatPixels & GetFloatPixels() const;
    void RenderFrameBuffer(float x, float y, float width, float height);
    
private:
    int _numStations;
    int _lightsPerStation;
    float _runwayLength;
    float _speedOfSound;
    float _archLength;
    float _framesPerSecond;
    
    ofFbo _frameBuffer;
    ofFloatPixels _floatPixelsCache;
};

#endif
