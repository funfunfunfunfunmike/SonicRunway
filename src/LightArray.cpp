//
//  LightArray.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/10/16.
//
//

#include "LightArray.hpp"
#include "Settings.hpp"

SrLightArray::SrLightArray(const SrSettings & settings) :
    _numX(settings.GetNumStations()),
    _numY(settings.GetLightsPerStation()),
    _data(_numX * _numY)
{
    
}

SrLightArray::~SrLightArray()
{
    
}

void
SrLightArray::SetColor(size_t x, size_t y, const ofColor & color)
{
    _data[_GetIndex(x,y)] = color;
}

void
SrLightArray::AddColor(size_t x, size_t y, const ofColor & color)
{
    _data[_GetIndex(x,y)] += color;
}

const ofColor &
SrLightArray::GetColor(size_t x, size_t y) const
{
    return _data[_GetIndex(x,y)];
}

size_t
SrLightArray::_GetIndex(size_t x, size_t y) const
{
    return x * _numY + y;
}

void
SrLightArray::Clear()
{
    for(size_t x = 0; x < _numX; x++) {
        for (size_t y = 0; y < _numY; y++) {
            SetColor(x, y, ofColor::black);
        }
    }
}
