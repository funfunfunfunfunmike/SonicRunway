
#include "ofApp.h"

#include "App.hpp"

//--------------------------------------------------------------
void ofApp::setup(){
    
    _app = new SrApp();
    
    // set the size of the window
    ofSetWindowShape(950, 550);
    
    ofSoundStreamSetup(2 /* nOutputs */,
                       2 /* nInputs */, this);
}

void ofApp::exit(){
    delete _app;
    
    ofSoundStreamStop();
    ofSoundStreamClose();
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    _app->AudioIn(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::update(){
    _app->Update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    _app->Draw();
}
