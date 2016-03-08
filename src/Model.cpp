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
    _lightsPerStation(59),
    _runwayLength(1000.0), // feet
    //_speedOfSound(1126.0), // feet per second
    _speedOfSound(500.0), // feet per second
    _archLength(30.0)      // feet
{
    _frameBuffer.allocate(_numStations, _lightsPerStation, GL_RGBA);
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
SrModel::GetArchLength() const
{
    return _archLength;
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
    
    ofTranslate(x, y);
    ofScale(width / _numStations, height / _lightsPerStation);
    _frameBuffer.draw(1, 1);
    
    ofPopMatrix();
    ofPopStyle();
}