//
//  Previs.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/3/16.
//
//

#ifndef SR_PREVIS_HPP
#define SR_PREVIS_HPP

#include <stdio.h>
#include "ofMain.h"

class SrModel;

class SrPrevis {
public:
    SrPrevis(SrModel * model);
    ~SrPrevis();
    
    void Update();
    void Draw(float x, float y, float width, float height);
    
private:
    SrModel *_model;
    float _lightRadius;
    
    //ofEasyCam _camera;
    ofCamera _camera;
};

#endif
