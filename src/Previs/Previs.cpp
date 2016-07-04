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
#include "Util.hpp"

SrPrevis::SrPrevis(SrModel * model, SrAudio * audio) :
    SrUiMixin("Previs"),
    _model(model),
    _audio(audio),
    _reverseAngleParam(false),
    _geomShaderDrawing(true),
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
    
    _SetupLights();
    
    _reverseAngleParam.setName("Reverse Angle");
    _AddUIParameter(_reverseAngleParam);

    _geomShaderDrawing.setName("Geom Shader [Advised]");
    _AddUIParameter(_geomShaderDrawing);
    
    _ReadAnimatedCameraData("previsCameraData.txt");
    
    _startAnimatedCameraButton.setName("Camera Animation");
    _startAnimatedCameraButton.addListener(this,
        &This::_OnStartAnimatedCameraButtonPressed);
    _AddUIParameter(_startAnimatedCameraButton);
    
}

SrPrevis::~SrPrevis()
{

}

void
SrPrevis::Draw(float x, float y, float width, float height)
{
    ofPushStyle();
    
    // Background
    ofSetColor(0,0,0,255);
    ofFill();
    ofDrawRectangle(x,y,width,height);
    
    // Start 3d Stuff here
    _camera.begin(ofRectangle(x,y,width,height));
    
    _environment.DrawBackground();
    
    _DrawLights();
    
    _environment.DrawBurners();
    
    // End 3d stuff
    _camera.end();
    
    ofPopStyle();
}

void
SrPrevis::_SetupLights()
{
    // Setup Lights Mesh
    
    _lightsMesh.setMode(OF_PRIMITIVE_POINTS);
    
    int numSpacesBetweenGates = _model->GetNumGates() - 1;
    float distanceBetweenGates = _model->GetDistanceBetweenGates();
    float circumference = _model->GetArchLength() * 4.0 / 3.0;
    float radius = circumference / (M_PI * 2.0);
    
    float groundToCenter = sin(M_PI / 4.0) * radius;
    
    int lastGateIdx = _model->GetLightsPerGate() - 1;
    
    for(int gate = 0; gate < _model->GetNumGates(); gate++) {
        for(int light = 0; light < _model->GetLightsPerGate(); light++) {
            
            float angle = (float) light / lastGateIdx * 3 * M_PI / 2;
            angle -= M_PI / 4.0;
            
            float y = gate * distanceBetweenGates;
            float x = cos(angle) * radius;
            float z = sin(angle) * radius + groundToCenter;
            
            _lightsMesh.addVertex(ofVec3f(x,y,z));
            _lightsMesh.addTexCoord(ofVec2f(gate, light));
            
        }
    }
    
     // Setup Lights Shader
    _dotLight.load(SrUtil_GetAbsolutePathForResource("light.png"));
    
    // Points come into geometry shader, tris come out
    _lightShader.setGeometryInputType( GL_POINTS );
    _lightShader.setGeometryOutputType( GL_TRIANGLE_STRIP );
    _lightShader.setGeometryOutputCount( 4 );
    _lightShader.load(SrUtil_GetAbsolutePathForResource("shaderVert.glsl"),
                      SrUtil_GetAbsolutePathForResource("shaderFrag.glsl"),
                      SrUtil_GetAbsolutePathForResource("shaderGeom.glsl"));
}

// Radius can be changed in geometry shader found in Resources
void
SrPrevis::_DrawLights(){
    
    // Draw with billboard geometry shader
    if ( _geomShaderDrawing )
    {
    
        // Bind a texture of the current gate pixel colors
        _textureForShader.setFromPixels(_model->GetFloatPixels());
    
        // Bind the shader that turns light pos verts into cards
        _lightShader.begin();
    
        _lightShader.setUniformTexture("lightPixelBuffer", _textureForShader, 1);
        _lightShader.setUniformTexture("lightDot", _dotLight, 2);
    
        // Draw the verts array of the light positions
        _lightsMesh.draw();
    
        // Unbind the shader
        _lightShader.end();
    }
    
    // Legacy DrawCircle draw mode
    else
    {
        std::vector<ofVec3f> verts = _lightsMesh.getVertices();
        const ofFloatPixels & pixels = _model->GetFloatPixels();

        int index = 0;
        for(int gate = 0; gate < _model->GetNumGates(); gate++) {
            for(int light = 0; light < _model->GetLightsPerGate(); light++) {
                
                ofVec3f p = verts[index];
                
                ofColor c = pixels.getColor(gate, light);
                ofColor drawColor(c[0], c[1], c[2], 255.0);
                ofSetColor(drawColor);
                
                ofPushMatrix();
                ofTranslate(p[0], p[1], p[2]);
                ofRotate(90,1.0,0.0,0.0);
                ofDrawCircle(0,0,0,.15);
                ofPopMatrix();
                
                index++;
            }
        }
    }
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
SrPrevis::_OnStartAnimatedCameraButtonPressed(bool &on)
{
    if( on ) {
        _animatedCameraIndex = 0;
    }
    else {
        _animatedCameraIndex = -1;
    }
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
