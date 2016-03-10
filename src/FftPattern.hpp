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

class SrFftBuffer;

///
/// A Pattern that renders the fftBuffer to the light array
///
class SrFftPattern : public SrPattern {
public:
    SrFftPattern(const std::string & name,
                 SrModel * model, SrAudio * audio,
                 SrFftBuffer * fftBuffer);
    virtual ~SrFftPattern();
    
    virtual void Update(const SrTime & now);
    virtual void Draw(const SrTime & now) const;
    
    float GetHueShift() const;
    void SetHueShift(float hueShift);
    
private:
    SrModel *_model;
    SrFftBuffer *_fftBuffer;
    float _hueShift;
    
    ofFloatPixels _pixels;
    
    ofFloatPixels _colorBuffer;
    
    SrFloatBuffer _hueShiftBuffer;
    
    ofxFloatSlider _hueShiftSlider;
};

#endif
