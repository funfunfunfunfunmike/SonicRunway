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
    
    void _SetupLights();
    void _DrawLights();
    void _ReadAnimatedCameraData(std::string fileName);
    void _OnStartAnimatedCameraButtonPressed(bool &on);
    
private:
    SrModel *_model;
    SrAudio *_audio;
    ofMesh _lightsMesh;
    
    ofShader _lightShader;
    ofImage _textureForShader;
    ofImage _dotLight;
    
    ofParameter<bool>_reverseAngleParam;
    ofParameter<bool>_geomShaderDrawing;
    int _animatedCameraIndex;
    
    std::vector<ofVec3f> _animatedCameraPositions;
    std::vector<ofVec3f> _animatedCameraLookAts;
    
    ofParameter<bool> _startAnimatedCameraButton;
    
    ofCamera _camera;
    SrEnvironment _environment;
    
};

#endif
