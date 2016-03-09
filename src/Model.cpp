//
//  Model.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/10/16.
//
//

#include "Model.hpp"

SrModel::SrModel() :
    _sampleRate(44100), // samples per second
    _bufferSize(1024),
    _numChannels(1),
    _buffersPerSecond((float) _sampleRate / _bufferSize),
    _numStations(30),
    _lightsPerStation(59),
    _runwayLength(1000.0), // feet
    _speedOfSound(1126.0), // feet per second
    //_speedOfSound(400.0), // feet per second
    _archLength(30.0),      // feet
    _framesPerSecond(60)
{
    _frameBuffer.allocate(_numStations, _lightsPerStation, GL_RGBA);
}

SrModel::~SrModel()
{
}

int
SrModel::GetSampleRate() const
{
    return _sampleRate;
}

int
SrModel::GetBufferSize() const
{
    return _bufferSize;
}

int
SrModel::GetNumChannels() const
{
    return _numChannels;
}

float
SrModel::GetBuffersPerSecond() const
{
    return _buffersPerSecond;
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
SrModel::GetArchLength() const
{
    return _archLength;
}

float
SrModel::GetFramesPerSecond() const
{
    return _framesPerSecond;
}

const ofFloatPixels &
SrModel::GetFloatPixels() const
{
    return _floatPixelsCache;
}

float
SrModel::ComputeDelayPerStation() const
{
    return GetRunwayLength() / GetNumStations() / GetSpeedOfSound();
}

float
SrModel::GetMaxBufferDuration() const
{
    return _numStations * 1.5 * ComputeDelayPerStation();
}

void
SrModel::Clear()
{
    _frameBuffer.begin();
    ofClear(0,0,0,255);
    _frameBuffer.end();
}

void
SrModel::BeginDrawing()
{
    _frameBuffer.begin();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
}

void
SrModel::EndDrawing()
{
    _frameBuffer.end();
    
    _frameBuffer.readToPixels(_floatPixelsCache);
}

void
SrModel::RenderFrameBuffer(float x, float y, float width, float height)
{
    ofPushStyle();
    ofPushMatrix();
    
    ofSetColor(255,255,255,255);
    ofDisableAntiAliasing();
    ofDisableSmoothing();
    
    ofTranslate(x, y);
    ofScale(width / _numStations, height / _lightsPerStation);
    _frameBuffer.draw(0, 0);
    
    ofPopMatrix();
    ofPopStyle();
}