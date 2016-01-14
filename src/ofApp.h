#pragma once

#include "ofMain.h"
#include "ofxAubio.h"
#include "ofxGui.h"

class SrApp;

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
    
    void audioIn(float * input, int bufferSize, int nChannels);

    /*
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    void audioOut();
     */


private:
    SrApp *_app;
};
