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

class SrFftBuffer;

class SrFftPattern : public SrPattern {
public:
    SrFftPattern(SrModel * model, SrAudio * audio, SrFftBuffer * fftBuffer);
    virtual ~SrFftPattern();
    
    virtual void Update(const SrTime & now);
    virtual void Draw(const SrTime & now) const;
    
private:
    SrModel *_model;
    SrFftBuffer *_fftBuffer;
    
    ofFloatPixels _pixels;
    
    ofFloatPixels _colorBuffer;
};

#endif
