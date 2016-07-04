#include "ofMain.h"
#include "ofApp.h"
#include "Util.hpp"

int main( ){
    
    // Change cwd so we can locate resource files.
    SrUtil_ChangeToResourceDirectory();
    
    // Setup the GL context
	ofSetupOpenGL(750, 250, OF_WINDOW);

	// This kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
