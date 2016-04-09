//
//  Environment.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 4/6/16.
//
//

#include "Environment.hpp"
#include "Util.hpp"

SrEnvironment::SrEnvironment() :
    SrUiMixin("Environment"),
    _backgroundEnabledParam("Enabled BG", true)
{
    _AddUIParameter(_backgroundEnabledParam);
    
    _skyImage.load(SrUtil_GetAbsolutePathForResource("skyTexture.png"));
    
    _skyMesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    float skyRadius = 4000;
    float skyHeight = 5000;
    
    int skyTextureWidth = 4096;
    int skyTextureHeight = 1024;
   
    int numSegments = 100;
    for(int i=0; i <= numSegments; i++) {
        float t = (float) i / numSegments;
        float angle = -t * M_PI * 2;
        
        float x = skyRadius * cosf(angle);
        float y = skyRadius * sinf(angle);
        
        _skyMesh.addVertex(ofVec3f(x, y, 0));
        _skyMesh.addVertex(ofVec3f(x, y, skyHeight));
        
        _skyMesh.addTexCoord(ofVec2f(t * skyTextureWidth, skyTextureHeight));
        _skyMesh.addTexCoord(ofVec2f(t * skyTextureWidth, 0));
    }
    
    _burner1Image.load(SrUtil_GetAbsolutePathForResource("burner1.png"));
    _burner2Image.load(SrUtil_GetAbsolutePathForResource("burner2.png"));
    
    _SetupBurnerMesh(&_burner1Mesh);
    _SetupBurnerMesh(&_burner2Mesh);
    
}

void
SrEnvironment::_SetupBurnerMesh(ofMesh *mesh)
{
    float burnerWidth = 6;
    float burnerHeight = 5.6;
    
    int burnerTextureWidth = 512;
    int burnerTextureHeight = 512;
    
    mesh->setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    mesh->addVertex(ofVec3f(-burnerWidth/2, 0, 0));
    mesh->addVertex(ofVec3f(-burnerWidth/2, 0, burnerHeight));
    mesh->addVertex(ofVec3f(burnerWidth/2, 0, 0));
    mesh->addVertex(ofVec3f(burnerWidth/2, 0, burnerHeight));
    
    mesh->addTexCoord(ofVec2f(0, burnerTextureHeight));
    mesh->addTexCoord(ofVec2f(0, 0));
    mesh->addTexCoord(ofVec2f(burnerTextureWidth, burnerTextureHeight));
    mesh->addTexCoord(ofVec2f(burnerTextureWidth, 0));
}

SrEnvironment::~SrEnvironment()
{
    
}

void
SrEnvironment::DrawBackground() const
{
    if (not _backgroundEnabledParam) {
        return;
    }
    
    ofSetColor(255,255,255);
    _skyImage.bind();
    _skyMesh.draw();
    _skyImage.unbind();
    
    // Ground plane
    ofPushMatrix();
    ofSetColor(10,10,10,255);
    ofDrawPlane(3000,3000);
    ofPopMatrix();
}

void
SrEnvironment::DrawBurners() const
{
    ofSetColor(255,255,255);
    
    ofPushMatrix();
    ofTranslate(0,1024);
    _burner1Image.bind();
    _burner1Mesh.draw();
    _burner1Image.unbind();
    ofPopMatrix();
    
    ofPushMatrix();
    ofTranslate(0,0);
    _burner2Image.bind();
    _burner2Mesh.draw();
    _burner2Image.unbind();
    ofPopMatrix();
    
}