//
//  Previs.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/3/16.
//
//

#include "Previs.hpp"
#include "Model.hpp"
#include "Audio.hpp"

SrPrevis::SrPrevis(SrModel * model, SrAudio * audio) :
    SrUiMixin("Previs"),
    _model(model),
    _audio(audio),
    _lightRadius(0.15),
    _reverseAngleParam(true),
    _animatedCameraIndex(-1)
{
    _AddUI(_environment.GetUiPanel());
    
    _camera.setFov(30);
    /*
    _camera.lookAt(ofVec3f(0,0,60),ofVec3f(0,1,0));
    _camera.setPosition(0,5.8,-18);
     */
    
    _camera.lookAt(ofVec3f(0,-60,0),ofVec3f(0,0,1));
    _camera.setPosition(0,1018,5.8);
    
    _reverseAngleParam.setName("Reverse Angle");
    _AddUIParameter(_reverseAngleParam);
    
    _ReadAnimatedCameraData("previsCameraData.txt");
    
    _startAnimatedCameraButton.setup("Start Camera Animation", 100, 20);
    _startAnimatedCameraButton.addListener(this,
        &This::_OnStartAnimatedCameraButtonPressed);
    _AddUI(&_startAnimatedCameraButton);
}

SrPrevis::~SrPrevis()
{
    
}

void
SrPrevis::_ReadAnimatedCameraData(std::string fileName)
{
    std::fstream myFile(fileName, std::ios_base::in);
    if (not myFile) {
        printf("Couldn't find animated camera file %s\n", fileName.c_str());
        return;
    }
    
    // 30 fps hack!  -- drops every other camera frame to facilitate recording
    // previs movie..
    /*
    float c0, c1, c2, l0, l1, l2;
    float x0, x1, x2, y0, y1, y2;
    while (myFile >> c0 >> c1 >> c2 >> l0 >> l1 >> l2 >>
             x0 >> x1 >> x2 >> y0 >> y1 >> y2) {
        _animatedCameraPositions.push_back(ofVec3f(c0,c1,c2));
        _animatedCameraLookAts.push_back(ofVec3f(l0,l1,l2));
    }
     */
    
    float c0, c1, c2, l0, l1, l2;
    while (myFile >> c0 >> c1 >> c2 >> l0 >> l1 >> l2) {
        _animatedCameraPositions.push_back(ofVec3f(c0,c1,c2));
        _animatedCameraLookAts.push_back(ofVec3f(l0,l1,l2));
    }
    
    printf("imported %zu camera frames\n", _animatedCameraPositions.size());
}

void
SrPrevis::_OnStartAnimatedCameraButtonPressed(const void *sender)
{
    _animatedCameraIndex = 0;
}

void
SrPrevis::Update()
{
    if (_animatedCameraIndex >= 0) {
        // Animated camera.
        _camera.setPosition(_animatedCameraPositions[_animatedCameraIndex]);
        _camera.lookAt(_animatedCameraLookAts[_animatedCameraIndex], ofVec3f(0,0,1));
        
        // Increment the camera index.  If we're off the end, set to -1 to stop
        // animation.
        _animatedCameraIndex++;
        if (_animatedCameraIndex >= _animatedCameraPositions.size()) {
            _animatedCameraIndex = -1;
        }
        
    } else {
        // Non-animated camera.
        
        if (_reverseAngleParam) {
            _camera.lookAt(ofVec3f(0,-60,0),ofVec3f(0,0,1));
            _camera.setPosition(0,1018,5.8);
        } else {
            _camera.lookAt(ofVec3f(0,60,0),ofVec3f(0,0,1));
            _camera.setPosition(0,-18,5.8);
        }
    }
}

void
SrPrevis::Draw(float x, float y, float width, float height)
{
    ofPushStyle();
    
    // Background
    ofSetColor(0,0,0,255);
    ofFill();
    ofDrawRectangle(x,y,width,height);
    
    // Start 3d stuff here
    _camera.begin(ofRectangle(x,y,width,height));
    
    _environment.DrawBackground();
    
    //_DrawSpheres(_lightRadius * 1.6, 60);
    _DrawSpheres(_lightRadius * 1.0, 255);
    
    _environment.DrawBurners();
    
    // End 3d stuff
    _camera.end();
    
    ofPopStyle();
}

void
SrPrevis::_DrawSpheres(float lightRadius, float transparency)
{
    int numSpacesBetweenGates = _model->GetNumGates() - 1;
    float distanceBetweenGates = _model->GetDistanceBetweenGates();
    float circumference = _model->GetArchLength() * 4.0 / 3.0;
    float radius = circumference / (M_PI * 2.0);
    
    const ofFloatPixels & pixels = _model->GetFloatPixels();
    
    float groundToCenter = sin(M_PI / 4.0) * radius;
    
    int lastGateIdx = _model->GetLightsPerGate() - 1;
    
    for(int gate = 0; gate < _model->GetNumGates(); gate++) {
        for(int light = 0; light < _model->GetLightsPerGate(); light++) {
            
            ofColor c = pixels.getColor(gate, light);
            ofColor drawColor(c[0], c[1], c[2], transparency);
            
            ofSetColor(drawColor);
            
            float angle = (float) light / lastGateIdx * 3 * M_PI / 2;
            angle -= M_PI / 4.0;
            
            float y = gate * distanceBetweenGates;
            float x = cos(angle) * radius;
            float z = sin(angle) * radius + groundToCenter;
           
            ofPushMatrix();
            ofTranslate(x,y,z);
            ofRotate(90,1.0,0.0,0.0);
            ofDrawCircle(0,0,0,lightRadius);
            ofPopMatrix();
        }
    }
    
}

void
SrPrevis::AudioOut(float * output, int bufferSize, int nChannels) const
{
    // Just use the Y position so we don't include a delay if we
    // are off to the side.  Clamp values to 0.
    float cameraY = _camera.getPosition()[1];
    if (cameraY < 0) {
        cameraY = 0;
    }
    
    float delay = cameraY / _model->GetSpeedOfSound();
    
    _audio->AudioOutDelayed(output, bufferSize, nChannels, delay);
}
