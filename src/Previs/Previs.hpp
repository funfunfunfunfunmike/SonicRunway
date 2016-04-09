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
#include "UiMixin.hpp"
#include "Environment.hpp"

class SrModel;
class SrAudio;

//
// A 3d respresntation of the tunnel of lights.
//
class SrPrevis : public SrUiMixin {
    typedef SrPrevis This;
    
public:
    SrPrevis(SrModel * model, SrAudio * audio);
    ~SrPrevis();
    
    void Update();
    void Draw(float x, float y, float width, float height);
    
    void AudioOut(float * output, int bufferSize, int nChannels) const;
    
private:
    void _DrawSpheres(float radius, float transparency);
    void _ReadAnimatedCameraData(std::string fileName);
    void _OnStartAnimatedCameraButtonPressed(const void * sender);
    
private:
    SrModel *_model;
    SrAudio *_audio;
    float _lightRadius;
    ofParameter<bool>_reverseAngleParam;
    int _animatedCameraIndex;
    
    std::vector<ofVec3f> _animatedCameraPositions;
    std::vector<ofVec3f> _animatedCameraLookAts;
    
    ofxButton _startAnimatedCameraButton;
    
    //ofEasyCam _camera;
    ofCamera _camera;
    SrEnvironment _environment;
    
};

#endif
