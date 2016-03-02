//
//  LightArray.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/10/16.
//
//

#ifndef _SR_LIGHT_ARRAY_HPP_
#define _SR_LIGHT_ARRAY_HPP_

#include <stdio.h>
#include <vector>

#include "ofMain.h"

class SrModel;

///
/// LightArray is a 2-dimensional array of ofColors representing
/// the current color of all the lights.  In each update/draw
/// cycle, the lightArray is cleared, and then each pattern
/// renders its results to this buffer
///
class SrLightArray {
public:
    SrLightArray(const SrModel &model);
    ~SrLightArray();
    
    void SetColor(size_t x, size_t y, const ofColor & color);
    void AddColor(size_t x, size_t y, const ofColor & color);
    const ofColor & GetColor(size_t x, size_t y) const;
    
    void Clear();
    
private:
    size_t _GetIndex(size_t x, size_t y) const;
   
private:
    size_t _numX;
    size_t _numY;
    std::vector<ofColor> _data;
};

#endif
