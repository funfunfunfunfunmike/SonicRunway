# SonicRunway

Experimenting with OpenFrameworks/Aubio/ArtNet for an LED sound visualization project.

Mac install instructions:

- Download and install XCode from the app store

- Install OpenFrameworks:  http://www.openframeworks.cc/download/
  follow xcode install documentation:  http://www.openframeworks.cc/setup/xcode/

- Install ofxAubio addon:  https://github.com/aubio/ofxAubio
  Follow git install instructions

- Install aubio library:
  Download and unzip aubio framework.
  http://aubio.org/bin/0.4.2/aubio-0.4.2.darwin_framework.zip

  Find 'aubio.framework' (under the parent directory)
  Move it to /Users/youruserid/Library/Frameworks (create directory if necessary)

- Clone this repo under <yourOpenFramworksDir>/apps/myApps/

- Open SonicRunway.xcodeproj

- From the top bar, next to the play/stop icons, make sure the 
  'Sonic Runway Debug' build target is selected.

- Build and run! 

You'll probably get some errors about 'aubio.h' not found.  
If so, you may need to delete and re-add 'aubio.framework' to 
the xcodeproj to get the header include path sorted.

Artnet:

libartnet source is copied from here:
https://code.google.com/p/open-lighting/downloads/list

... but included in this project (along with attribution/copying info)

