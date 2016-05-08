//
//  StripesPattern.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/22/16.
//
//

#ifndef SR_STRIPES_PATTERN_HPP
#define SR_STRIPES_PATTERN_HPP

#include "ScrollingPattern.hpp"

//
// SrStripesPattern
//
class SrStripesPattern : public SrScrollingPattern {
public:
    SrStripesPattern(const std::string & name,
                     SrModel * model, SrAudio * audio);
    virtual ~SrStripesPattern();
    
protected:
    virtual void _Update();
    virtual void _DrawCurrentStation(std::vector<ofColor> * buffer) const;
    
private:
    ofParameter<float> _hueParam;
    ofParameter<int> _numStripesParam;
    ofParameter<float> _spinSpeedParam;
    
    float _angle;
};


#endif
