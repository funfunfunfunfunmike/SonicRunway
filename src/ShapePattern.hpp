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

///
/// A Pattern that draws shapes that coorespond to audio events.
///
class SrShapePattern : public SrPattern {
public:
    SrShapePattern(const std::string & name,
                   SrModel * model, SrAudio * audio);
    virtual ~SrShapePattern();
    
    virtual void Update(const SrTime & now);
    virtual void Draw(const SrTime & now) const;
    
private:
    std::set<SrShape *> _shapes;
    
    bool _isOddBeat;
};

#endif