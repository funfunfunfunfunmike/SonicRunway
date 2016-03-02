//
//  GridDisplay.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 1/11/16.
//
//

#include "GridDisplay.hpp"
#include "Model.hpp"

#include "ofMain.h"

SrGridDisplay::SrGridDisplay(SrModel *model,
                             float x, float y,
                             float width, float height) :
    _model(model),
    _x(x),
    _y(y),
    _width(width),
    _height(height)
{
    
}

SrGridDisplay::~SrGridDisplay()
{
    
}

void
SrGridDisplay::Draw()
{
    /*
    ofSetColor(10, 10, 10);
    ofDrawRectangle(_x, _y, _width, _height);
    
    float margin = 10.0;
    float radius = 5.0;
    
    int nStations = _model->GetNumStations();
    int nLightsPerStation = _model->GetLightsPerStation();
    
    float widthPerStation = (_width - margin * 2.0) / nStations;
    float heightPerLight = (_height - margin * 2.0) / nLightsPerStation;
    
    for (int stationIdx = 0; stationIdx < nStations; stationIdx++) {
        for (int lightIdx = 0;
             lightIdx < nLightsPerStation; lightIdx++) {
           
            float x = margin + widthPerStation * stationIdx;
            float y = margin + heightPerLight * lightIdx;
           
            ofSetColor(_lightArray->GetColor(stationIdx, lightIdx));
            ofFill();
            ofDrawCircle(_x + x, _y + y, radius);
        }
    }
    */
        
}
