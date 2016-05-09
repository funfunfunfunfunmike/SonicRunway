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

//
// Model class for the app.  Holds global settings and
// the main frame buffer that store the color of all the lights.
//
//
class SrModel {
public:
    SrModel();
    ~SrModel();
    
    void Update();
    
    int GetSampleRate() const;
    int GetBufferSize() const;
    int GetNumChannels() const;
    float GetBuffersPerSecond() const;
    
    // XXX Gate 0 is assumed to be at the sound source, though it
    // probably won't exist in the actual installation.  So this
    // number may be higher than the number of physical gates by
    // one or two.
    int GetNumGates() const;
    int GetLightsPerGate() const;
    
    float GetDistanceBetweenGates() const; // in feet
    float GetSpeedOfSound() const; // in feet per second
    float GetArchLength() const;  // in feet
    int ComputeFramesPerSecond() const;
    
    // Get the frame rate relative to the speed of sound across the
    // gates.  1 frame per gate means it takes one update/draw
    // cycle for sound to travel from one gate to the next.
    int GetFramesPerGate() const;
    
    // XXX maybe replace this with DelayAtGate to prevent
    // assumptions about the distance to the first gate??
    float ComputeDelayPerGate() const; // in seconds
    float GetMaxBufferDuration() const; // in seconds
    
    void Clear();
    void BeginDrawing();
    void EndDrawing();
    
    const ofFloatPixels & GetFloatPixels() const;
    void RenderFrameBuffer(float x, float y, float width, float height);
    
private:
    int _sampleRate;
    int _bufferSize;
    int _numChannels;
    float _buffersPerSecond;
    
    int _numGates;
    int _lightsPerGate;
    float _distanceBetweenGates;
    float _speedOfSound;
    float _archLength;
    int _framesPerGate;
    
    ofFbo _frameBuffer;
    ofFloatPixels _floatPixelsCache;
};

#endif
