//
//  FftPattern.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/4/16.
//
//

#ifndef SR_FFT_PATTERN_HPP
#define SR_FFT_PATTERN_HPP

#include <stdio.h>

#include "Pattern.hpp"
#include "Shape.hpp"
#include "Buffer.hpp"

//
// A Pattern that renders the fftBuffer to the light array
//
class SrFftPattern : public SrPattern {
public:
    SrFftPattern(const std::string & name,
                 SrModel * model, SrAudio * audio);
    virtual ~SrFftPattern();
    
protected:
    virtual void _Update(const SrTime & now);
    virtual void _Draw(const SrTime & now) const;
    
private:
    SrModel *_model;
    ofParameter<float> _hueShiftParam;
    
    ofFloatPixels _pixels;
    
    SrFloatBuffer _hueShiftBuffer;
};

#endif
