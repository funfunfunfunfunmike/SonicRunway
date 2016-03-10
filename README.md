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

- Install essentia audio analysis library (with homebrew):
    https://github.com/MTG/homebrew-essentia
    This should end up under /usr/local/

- Install boost (with homebrew):
    (XXX - not actually used... yet)
    brew install boost --without-python

- Clone this repo under (yourOpenFramworksDir)/apps/myApps/

- Open SonicRunway.xcodeproj

- From the top bar, next to the play/stop icons, make sure the 
  'Sonic Runway Debug' build target is selected.

- Build and run! 

You'll probably get some errors about 'aubio.h' not found.  
If so, you may need to delete and re-add 'aubio.framework' to 
the xcodeproj to get the header include path sorted.


TODO:

- Replace SrTime concepts with regular floats

- Refactor Onset and fft to use the new circular buffer.

- Fix up anti-aliasing issues with rendering

- Add some UI with knobs for various settings
