# SonicRunway

Software control for Sonic Runway art installation, a visualization of the
speed of sound.  

See http://sonicrunway.net

Mac install instructions:

- Download and install XCode from the app store.  I'm using 7.2:
    https://developer.apple.com/xcode/download/

- Install OpenFrameworks:  http://www.openframeworks.cc/download/
  follow xcode install documentation:  http://www.openframeworks.cc/setup/xcode/

- Install ofxAubio addon:  https://github.com/aubio/ofxAubio
  Just clone the repository into the addons directory.
  Don't do the the fetch_aubio_framework.sh part


- **Temporary note:** The most recent version of ofxAubio is incompatible with
  our current code. You must adjust your local install to use an older version,
  like so:
```
git checkout -b withreceive b493b9f8ab982a96911fe69eaebb198fa23f6022
```
  This creates a local branch called `withreceive` that tracks the remote commit.
  Rob will fix this soon.

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
the xcodeproj to get the header include path sorted.  To do 
that:
  - in Xcode, right click 'aubio.framework' and choose 'Delete'
  - choose 'Remove Reference' (don't move to trash)
  - Find aubio.framework wherefer you put it and drag it from
    the finder into the Xcode panel.

OVERVIEW:

The app uses OpenFrameworks, which is kinda like Processing but C++.
It wraps OpenGL and other lower level libraries with a convenient
API so you can set up a window, get audio, and draw stuff.  
There are a lot of 'extensions' available to provide other 
functionality.  

Lots of good info on OpenFrameworks here:

    http://openframeworks.cc/ofBook/chapters/foreword.html

or the source for the book:

    https://github.com/openframeworks/ofBook/

Basically, the program:
  - gets audio input
  - processes the audio input to extract fft and other cues
  - renders a bunch of patterns to a buffer
  - broadcasts the buffer to the LEDs

The 'SrBuffer' class is a generic circular buffer that can store
samples of a parameter value.  It can then be queried per station.
This provides the history necessary to make patterns that ripple
down the runway at the speed of sound.  

It's important to note that the audio processing and render/draw
functions are called from different threads and at different 
intervals.  So far, I haven't bothered making things truly 
thread safe because the various buffers are all statically 
allocated. So, we may see some visual tearing.  If this becomes 
problematic we can use ofMutex to make it thread safe.


TODO:

- Sync latest aubio repository and fix up our code.

- Fix or standardize path to aubio.framework in project file?

- Move audio output to Previs class.  Use a buffer to delay audio playback
  so we can see what it looks like from the other end of the runway.

- Replace SrTime concepts with regular floats and ofGetElapsedTime?

- Provide a generic UI widget for graphing a buffer.  Allow patterns
  to publish these values for debugging.

- Replace binary 'onset' and beat detection with something fuzzier --
  perhaps a few band-pass filters piped into RMS?

- Add some UI with knobs for various settings

- Allow patterns to be turned on/off.  Or perhaps pass them a history-
  buffered alpha value.

- Make Fft and other filters automatically adjust to global volume level.

- Hook up a second station and figure out how to broadcast to multiple
  boards.
