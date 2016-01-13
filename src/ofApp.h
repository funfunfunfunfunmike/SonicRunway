#pragma once

#include "ofMain.h"
#include "ofxAubio.h"
#include "ofxGui.h"

#include "Audio.hpp"
#include "AudioUI.hpp"
#include "Settings.hpp"
#include "Cues.hpp"
#include "LightArray.hpp"
#include "GridDisplay.hpp"
#include "OnsetPattern.hpp"

///
/// Main openFrameworks app.  This handles creating a window,
/// getting events, and drawing.
///
class ofApp : public ofBaseApp{

public:
    void setup();
    void exit();

    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    void audioIn(float * input, int bufferSize, int nChannels);
    void audioOut();

private:
    SrSettings _settings;
    SrCues _cues;
    SrLightArray _lightArray;
    SrAudio _audio;
    SrAudioUI _audioUI;
    SrOnsetPattern _onsetPattern;
    SrGridDisplay _gridDisplay;
};
