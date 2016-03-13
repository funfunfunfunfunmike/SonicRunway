//
//  ShapePattern.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/2/16.
//
//

#include "ShapePattern.hpp"
#include "Audio.hpp"

SrShapePattern::SrShapePattern(const std::string & name,
                               SrModel * model, SrAudio * audio) :
    SrPattern(name, model, audio),
    _isOddBeat(false)
{
    
}

SrShapePattern::~SrShapePattern()
{
    // Destroy all shapes
    for(auto iter = _shapes.begin(); iter != _shapes.end(); iter++) {
        delete *iter;
    }
    
    _shapes.clear();
}

void
SrShapePattern::Update(const SrTime & now)
{
    SrTime expiration = now - SrSeconds(3);
    
    // Remove expired shapes
    for(auto iter = _shapes.begin(); iter != _shapes.end(); ) {
        SrShape *shape = *iter;
        if (shape->GetTime() < expiration) {
            iter = _shapes.erase(iter);
            delete shape;
        } else {
            ++iter;
        }
    }
    
    const SrOnsetDetect & lowOnset = GetAudio()->GetLowOnset();
    SrTime timeOfLastOnset = lowOnset.GetTimeOfLastOnset();
    
    // If no new onsets have been detected, we are done.
    if (timeOfLastOnset == _timeOfLastShape) {
        return;
    }
    
    SrShape * newShape =
        new SrOnsetShape(GetModel(), now, ofColor(10, 0, 0, 255), 0.5);
    
    _shapes.insert(newShape);
    
    _timeOfLastShape = timeOfLastOnset;
}

void
SrShapePattern::Draw(const SrTime & now) const
{
    for(auto iter = _shapes.begin(); iter != _shapes.end(); iter++) {
        SrShape *shape = *iter;
        shape->Draw(now);
    }
}
