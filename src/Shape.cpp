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
    printf("constructed shape\n");
}

SrShape::~SrShape()
{
    printf("destroyed shape\n");
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
   
    return distanceFromSource / nStations;
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
    ofSetColor(_color);

    float xPos = GetXPosition(now);
    
    float height = GetModel()->GetLightsPerStation();
    float width = 2.0;
    ofDrawRectangle(xPos - width, 0.0, width, height);
}