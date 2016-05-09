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
#include "SimpleBuffer.hpp"
#include "UiMixin.hpp"
#include <string>

class SrModel;
class SrAudio;

//
// Base class for patterns that draw themselves to the array
// of lights.  Subclasses should implement Update and Draw.
//
// SrPatterns are expected to update every LED for every frame.
// If you're making a pattern that is intended to stream down
// the runway at the speed of sound, and doesn't change as
// it ripples down, consider deriving from SrScrollingPattern
// instead.
//
// Pattern instances are created and owned by SrApp.
//
class SrPattern : public SrUiMixin {
public:
    SrPattern(const std::string & name, SrModel * model, SrAudio * audio);
    virtual ~SrPattern();
    
    // Called by the main app to update state.
    // Subclasses should implement _Update()
    void Update();
    
    // Called by the main app to render the pattern to the
    // light buffer.  Subclasses should implement _Draw()
    void Draw();
    
    // Get a buffer that contains the history of the
    // 'enabled' parameter (the checkbox that turns it on/off)
    const SrFloatSimpleBuffer & GetEnabled() const;
    
    // Set the current value of 'enabled'.  This will be
    // buffered across time.
    void SetEnabled(bool enabled);
    
protected:
    
    // Update the pattern in response to the current state.
    // Prepare to draw.
    virtual void _Update() = 0;
    
    // Draw the pattern.  By the time this is called, the render
    // state will be set to draw to a frame buffer that represents
    // the lights.
    //   X coordinates are [0, numGates).
    //   Y coordinates are [0, lightsPerGate).
    //
    // Blend mode is OF_BLENDMODE_ADD so the color values will
    // sum together.
    //
    // Patterns should respect per-gate values from the 'Enabled'
    // buffer, and not draw anything when/where they are disabled.
    virtual void _Draw() const = 0;
    
    SrModel * GetModel() const;
    SrAudio * GetAudio() const;
    
private:
    SrModel *_model;
    SrAudio *_audio;
    SrFloatSimpleBuffer _enabledBuffer;
    ofParameter<bool> _enabledParam;
    
    ofxToggle _enabledToggle;
};

#endif
