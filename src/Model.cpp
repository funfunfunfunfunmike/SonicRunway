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
    _bufferSize(1024),  // for audio input
    _numChannels(1),
    _buffersPerSecond((float) _sampleRate / _bufferSize),
    _numGates(33),  // Gate 0 exists in software, but not physically..
    _lightsPerGate(277),
    _distanceBetweenGates(32.0), // feet
    _speedOfSound(1126.0), // feet per second
    _archLength(31.0),     // feet
    _framesPerGate(1)
{
    _parameterGroup.setName("Runway");
    _frameBuffer.allocate(_numGates, _lightsPerGate, GL_RGBA);
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
SrModel::GetNumGates() const
{
    return _numGates;
}

int
SrModel::GetLightsPerGate() const
{
    return _lightsPerGate;
}

float
SrModel::GetDistanceBetweenGates() const
{
    return _distanceBetweenGates;
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

int
SrModel::GetFramesPerGate() const
{
    return _framesPerGate;
}

int
SrModel::ComputeFramesPerSecond() const
{
    return round((float) _framesPerGate / ComputeDelayPerGate());
}

const ofFloatPixels &
SrModel::GetFloatPixels() const
{
    return _floatPixelsCache;
}

float
SrModel::ComputeDelayPerGate() const
{
    return GetDistanceBetweenGates() / GetSpeedOfSound();
}

float
SrModel::GetMaxBufferDuration() const
{
    return _numGates * 1.5 * ComputeDelayPerGate();
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
    ofPushStyle();
    _frameBuffer.begin();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
}

void
SrModel::EndDrawing()
{
    _frameBuffer.end();
    
    _frameBuffer.readToPixels(_floatPixelsCache);
    ofPopStyle();
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
    //ofScale(width / _numGates, height / _lightsPerGate);
    _frameBuffer.draw(0, 0, width, height);
    
    ofPopMatrix();
    ofPopStyle();
}

ofParameterGroup &
SrModel::GetParameterGroup()
{
    return _parameterGroup;
}
