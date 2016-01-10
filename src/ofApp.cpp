
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // set the size of the window
    ofSetWindowShape(750, 250);
    
    _audio.Setup(this);

    ofSoundStreamSetup(2 /* nOutputs */,
                       2 /* nInputs */, this);
    
    _audioUI.Setup(&_audio, 10.0, 10.0);
}

void ofApp::exit(){
    _audio.Exit();
    _audioUI.Exit();
    ofSoundStreamStop();
    ofSoundStreamClose();
}

void ofApp::audioIn(float * input, int bufferSize, int nChannels){
    _audio.AudioIn(input, bufferSize, nChannels);
}

void audioOut(){
}

//--------------------------------------------------------------
void ofApp::update(){
    _audio.Update();
    _audioUI.Update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    _audioUI.Draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
