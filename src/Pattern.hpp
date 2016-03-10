//
//  Pattern.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/2/16.
//
//

#ifndef SR_PATTERN_HPP
#define SR_PATTERN_HPP

#include <stdio.h>

#include "Types.hpp"
#include "ofxGui.h"
#include <string>

class SrModel;
class SrAudio;

///
/// Base class for patterns that draw themselves to the array
/// of lights.  Subclasses should implement Update and Draw.
///
class SrPattern {
public:
    SrPattern(const std::string & name, SrModel * model, SrAudio * audio);
    virtual ~SrPattern();
    
    // Update the pattern in response to the current state.
    // Prepare to draw.
    virtual void Update(const SrTime & now) = 0;
    
    // Draw the pattern.  By the time this is called, the render
    // state will be set to draw to a frame buffer that represents
    // the lights.
    //   X coordinates are [0, numStations).
    //   Y coordinates are [0, lightsPerStation).
    //
    // Blend mode is OF_BLENDMODE_ADD so the color values will
    // sum together.
    virtual void Draw(const SrTime & now) const = 0;
    
    // XXX dangerously mixing UI and implementation!
    void SetUIPosition(float x, float y);
    void DrawUI();
    
protected:
    
    SrModel * GetModel() const;
    SrAudio * GetAudio() const;
    
    // Subclasses call this from their constructor to
    // Add UI elements to the panel for this pattern.
    void _AddUI(ofxBaseGui * item);
    
private:
    SrModel *_model;
    SrAudio *_audio;
    
    ofxPanel _panel;
};

#endif
