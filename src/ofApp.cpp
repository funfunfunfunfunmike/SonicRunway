
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    _settings.Setup();
    
    // set the size of the window
    ofSetWindowShape(950, 550);
    
    _audio.Setup();
    _cues.Setup(&_audio);
    _lightArray.Setup(_settings);

    ofSoundStreamSetup(2 /* nOutputs */,
                       2 /* nInputs */, this);
    
    _audioUI.Setup(&_audio, 10.0, 10.0);
    _onsetPattern.Setup(&_settings, &_lightArray, &_cues);
    _gridDisplay.Setup(&_lightArray, &_settings, 10.0, 230.0, 930.0, 300.0);
}

void ofApp::exit(){
    _audio.Exit();
    _audioUI.Exit();
    _onsetPattern.Exit();
    _gridDisplay.Exit();
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
    SrTime now = std::chrono::system_clock::now();
    
    _audio.Update();
    _cues.Update(now);
    
    _lightArray.Clear();
    _onsetPattern.Update(now);
    
    _audioUI.Update();
    _gridDisplay.Update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(40,40,40);
    _audioUI.Draw();
    _gridDisplay.Draw();
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
