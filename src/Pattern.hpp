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

class SrModel;
class SrAudio;

///
/// Base class for patterns that draw themselves to the array
/// of lights.  Subclasses should implement Update and Draw.
///
class SrPattern {
public:
    SrPattern(SrModel * model, SrAudio * audio);
    virtual ~SrPattern();
    
    // Update the pattern in response to the current audio.
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
    
    SrModel * GetModel() const;
    SrAudio * GetAudio() const;
    
private:
    SrModel *_model;
    SrAudio *_audio;
};

#endif
