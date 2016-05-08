//
//  ScrollingPattern.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 5/5/16.
//
//

#ifndef SR_SCROLLING_PATTERN_HPP
#define SR_SCROLLING_PATTERN_HPP

#include <stdio.h>

#include "Pattern.hpp"

//
// ScScrollingPattern is an SrPattern that automatically scrolls
// down the runway at the speed of sound.  Subclasses only need to
// implement _DrawCurrentStation, and SrScrollingPattern keeps track
// of the buffer and renders the rest of the stations appropriately.
//
class SrScrollingPattern : public SrPattern {
public:
    SrScrollingPattern(const std::string & name,
                       SrModel * model, SrAudio * audio);
    ~SrScrollingPattern();
    
protected:
    // Implemented from SrPattern
    virtual void _Update(const SrTime & now);
    virtual void _Draw(const SrTime & now) const;
    
    // Subclasses implement this to draw the current station.
    virtual void _DrawCurrentStation(std::vector<ofColor> * buffer) const = 0;
    
private:
    int _index;
    
    ofImage _image;
};

#endif
