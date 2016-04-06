#include "ofMain.h"
#include "ofApp.h"
#include "Util.hpp"

//
int main( ){
    
    // Change cwd so we can locate resource files.
    SrUtil_ChangeToResourceDirectory();
    
	ofSetupOpenGL(750, 250, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
