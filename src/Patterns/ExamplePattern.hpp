//
//  StripePattern.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/17/16.
//
//

#ifndef SR_EXAMPLE_PATTERN_HPP
#define SR_EXAMPLE_PATTERN_HPP

#include <stdio.h>
#include "Pattern.hpp"
#include "Buffer.hpp"

//
// SrExamplePattern is a really simple pattern that just illuminates
// a single LED for each station.  It is meant to demonstrate how
// to set up parameters and buffer their values across the length
// of the runway.
//
class SrExamplePattern : public SrPattern {
public:
    SrExamplePattern(const std::string & name,
                    SrModel * model, SrAudio * audio);
    virtual ~SrExamplePattern();
    
protected:
    virtual void _Update(const SrTime & now);
    virtual void _Draw(const SrTime & now) const;
    
private:
    ofParameter<float> _hueParam;
    ofParameter<float> _angleParam;
    
    SrFloatBuffer _hueBuffer;
    SrFloatBuffer _angleBuffer;
};


#endif
