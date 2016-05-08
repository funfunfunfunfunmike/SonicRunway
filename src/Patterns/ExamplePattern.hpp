//
//  StripePattern.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/17/16.
//
//

#ifndef SR_EXAMPLE_PATTERN_HPP
#define SR_EXAMPLE_PATTERN_HPP

#include "ScrollingPattern.hpp"

//
// SrExamplePattern is a really simple pattern that just illuminates
// a single LED for each station.  It is meant to demonstrate how
// to set up parameters and draw.
//
class SrExamplePattern : public SrScrollingPattern {
public:
    SrExamplePattern(const std::string & name,
                    SrModel * model, SrAudio * audio);
    virtual ~SrExamplePattern();
    
protected:
    virtual void _DrawCurrentStation(std::vector<ofColor> * buffer) const;
    
private:
    ofParameter<float> _hueParam;
    ofParameter<float> _angleParam;
};


#endif
