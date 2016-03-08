//
//  FftBuffer.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/6/16.
//
//

#ifndef SR_FFT_BUFFER_HPP
#define SR_FFT_BUFFER_HPP

#include <stdio.h>
#include "ofMain.h"

class SrModel;

class SrFftBuffer {
public:
    SrFftBuffer(int numBands,
                int sampleRate, int bufferSize,
                int framesPerSecond,
                float delayPerStation);
    virtual ~SrFftBuffer();
    
    // Input one buffer's fft results.  Called once
    // per 'AudioIn'
    void FftIn(float * energies);
    
    // Update the cache.  Called once per frame
    void Update();
    
    // Draw the greyscale pattern
    void Draw(float x, float y, float width, float height) const;
    float GetBuffersPerSecond() const;
    float GetBufferLengthInSeconds() const;
    
    const ofFloatPixels & GetData() const;
    const ofFloatPixels & GetPerStationData() const;
    
private:
    int _numBands;
    int _sampleRate;
    int _bufferSize;
    int _framesPerSecond;
    float _buffersPerSecond;
    float _bufferLengthInSeconds;
    float _delayPerStation;
    
    int _xPos;
    ofFloatPixels _rollingBuffer;
    ofFloatPixels _outputBuffer;
    ofFloatPixels _perStationBuffer;
};

#endif