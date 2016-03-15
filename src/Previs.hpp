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

//
// A 3d respresntation of the tunnel of lights.
//
class SrPrevis {
public:
    SrPrevis(SrModel * model, SrAudio * audio);
    ~SrPrevis();
    
    void Update();
    void Draw(float x, float y, float width, float height);
    
    void AudioOut(float * output, int bufferSize, int nChannels);
    
private:
    void _DrawSpheres(float radius, float transparency);
    
private:
    SrModel *_model;
    float _lightRadius;
    
    //ofEasyCam _camera;
    ofCamera _camera;
};

#endif
