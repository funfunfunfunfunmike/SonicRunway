//
//  Shape.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/2/16.
//
//

#ifndef SR_SHAPE_HPP
#define SR_SHAPE_HPP

#include "Types.hpp"
#include <stdio.h>
#include "ofMain.h"

class SrModel;

//
// A shape primitive used by SrShape pattern
//
class SrShape {
public:
    SrShape(SrModel * model, const SrTime & time);
    virtual ~SrShape();
    
    SrTime GetTime() const;
    float GetAge(const SrTime & now) const;
    
    virtual void Draw(const SrTime &now) const = 0;
    
    SrModel * GetModel() const;
    
    float GetXPosition(const SrTime &now) const;
    
private:
    SrModel * _model;
    SrTime _time;
};

class SrOnsetShape : public SrShape {
public:
    SrOnsetShape(SrModel * model,
                 const SrTime & time,
                 const ofColor & color,
                 float yPos);
    
    virtual ~SrOnsetShape();
    
    virtual void Draw(const SrTime &now) const;
    
private:
    ofColor _color;
    float _yPos;
};

#endif
