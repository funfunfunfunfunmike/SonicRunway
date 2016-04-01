//
//  StripesPattern.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/22/16.
//
//

#ifndef SR_STRIPES_PATTERN_HPP
#define SR_STRIPES_PATTERN_HPP

#include <stdio.h>
#include "Pattern.hpp"
#include "Buffer.hpp"

//
// SrStripesPattern
//
class SrStripesPattern : public SrPattern {
public:
    SrStripesPattern(const std::string & name,
                     SrModel * model, SrAudio * audio);
    virtual ~SrStripesPattern();
    
protected:
    virtual void _Update(const SrTime & now);
    virtual void _Draw(const SrTime & now) const;
    
private:
    ofParameter<float> _hueParam;
    ofParameter<int> _numStripesParam;
    ofParameter<float> _spinSpeedParam;
    
    SrFloatBuffer _hueBuffer;
    SrFloatBuffer _angleBuffer;
    SrIntBuffer _numStripesBuffer;
    
    float _currentAngle;
};


#endif
