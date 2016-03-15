//
//  ShapePattern.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/2/16.
//
//

#ifndef SR_SHAPE_PATTERN_HPP
#define SR_SHAPE_PATTERN_HPP

#include <stdio.h>

#include "Pattern.hpp"
#include "Shape.hpp"

//
// A Pattern that draws shapes that coorespond to audio events.
//
// XXX this may be retired in favor of something 'fuzzier', since
// the boolean detection of onsets and beats is prone to errors that
// make the visualization unsatisfying.
//
class SrShapePattern : public SrPattern {
public:
    SrShapePattern(const std::string & name,
                   SrModel * model, SrAudio * audio);
    virtual ~SrShapePattern();
    
protected:
    virtual void _Update(const SrTime & now);
    virtual void _Draw(const SrTime & now) const;
    
private:
    std::set<SrShape *> _shapes;
    SrTime _timeOfLastOnset;
    SrTime _timeOfLastBeat;
    
    bool _isOddBeat;
};

#endif