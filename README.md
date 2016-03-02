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

- Clone this repo under (yourOpenFramworksDir)/apps/myApps/

- Open SonicRunway.xcodeproj

- From the top bar, next to the play/stop icons, make sure the 
  'Sonic Runway Debug' build target is selected.

- Build and run! 

You'll probably get some errors about 'aubio.h' not found.  
If so, you may need to delete and re-add 'aubio.framework' to 
the xcodeproj to get the header include path sorted.



TODO:

- Refactor LightArray to just be an ofImage or Fbo.  Scrape this to Artnet output.

- Make a 3D tunnel visualization to match the structure

- Add beat-based patterns

- Add EQ-based patterns

- Add some UI with knobs for various settings

---------------------

Plan:
  - Get rid of cues.
  - Audio returns current events that patterns can read.

  - patterns may own shapes that move down runway
      default shape updates its coords automatically
  - model can draw Fbo directly to UI (maybe scaled)
  - previs draws 3d previs
  - artnet sends to pixels
