//
//  Shape.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/2/16.
//
//

#include "Shape.hpp"
#include "Model.hpp"

SrShape::SrShape(SrModel * model, const SrTime & time) :
    _model(model),
    _time(time)
{
}

SrShape::~SrShape()
{
}

SrModel *
SrShape::GetModel() const
{
    return _model;
}

SrTime
SrShape::GetTime() const
{
    return _time;
}

float
SrShape::GetAge(const SrTime &now) const
{
    std::chrono::duration<float> timeSince = now - _time;
    return timeSince.count();
}

float
SrShape::GetXPosition(const SrTime &now) const
{
    int nStations = _model->GetNumStations();
    float speedOfSound = _model->GetSpeedOfSound();
    
    float age = GetAge(now);
    
    float distanceFromSource = age * speedOfSound;
   
    float distancePerStation = _model->GetRunwayLength() / _model->GetNumStations();
    
    return distanceFromSource / distancePerStation;
}

//-----------------------------------------------------------

SrOnsetShape::SrOnsetShape(SrModel * model,
                           const SrTime & time,
                           const ofColor & color,
                           float yPos) :
    SrShape(model, time),
    _color(color),
    _yPos(yPos)
{
    
}

SrOnsetShape::~SrOnsetShape()
{
    
}

void
SrOnsetShape::Draw(const SrTime &now) const
{
    ofSetColor(_color * 2.0);

    float xPos = GetXPosition(now);
    
    float height = GetModel()->GetLightsPerStation();
    float width = 1.0;
    ofDrawRectangle(xPos - width, 0.0, width, height);
    ofSetColor(_color * 0.6);
    ofDrawTriangle(xPos, 0.0, xPos-8, 0.0, xPos, height * 0.8);
    ofDrawTriangle(xPos, height, xPos-8, height, xPos, height * 0.2);
    /*
    ofDrawRectangle(xPos - width * 2, 0.0, width, height);
    ofSetColor(_color * 0.3);
    ofDrawRectangle(xPos - width * 3, 0.0, width, height);
    ofSetColor(_color * 0.1);
    ofDrawRectangle(xPos - width * 4, 0.0, width, height);
     */
}