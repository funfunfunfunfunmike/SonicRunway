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
class SrSettings;

///
/// SrGridDisplay - a 2d rendering of the lightArray for debugging
/// purposes.
///
class SrGridDisplay {
public:
    void Setup(SrLightArray * lightArray,
               SrSettings * settings,
               float x, float y,
               float width, float height);
    void Update();
    void Draw();
    void Exit();
    
private:
    SrLightArray *_lightArray;
    SrSettings *_settings;
    float _x;
    float _y;
    float _width;
    float _height;
};

#endif
