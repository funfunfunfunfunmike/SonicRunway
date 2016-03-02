//
//  GridDisplay.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/11/16.
//
//

#ifndef SR_GRID_DISPLAY_HPP
#define SR_GRID_DISPLAY_HPP

#include <stdio.h>

class SrLightArray;
class SrModel;

///
/// SrGridDisplay - a 2d rendering of the lightArray for debugging
/// purposes.
///
class SrGridDisplay {
public:
    SrGridDisplay(SrLightArray * lightArray,
                  SrModel * model,
                  float x, float y,
                  float width, float height);
    ~SrGridDisplay();
    
    void Update();
    void Draw();
    
private:
    SrLightArray *_lightArray;
    SrModel *_model;
    float _x;
    float _y;
    float _width;
    float _height;
};

#endif
