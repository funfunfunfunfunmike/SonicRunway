//
//  Environment.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 4/6/16.
//
//

#ifndef SR_ENVIRONMENT_HPP
#define SR_ENVIRONMENT_HPP

#include "UiMixin.hpp"

#include <stdio.h>
#include "ofMain.h"

class SrEnvironment : public SrUiMixin
{
public:
    SrEnvironment();
    ~SrEnvironment();
    
    void DrawBackground() const;
    void DrawBurners() const;
    
private:
    void _SetupBurnerMesh(ofMesh *mesh);
    
private:
    ofParameter<bool> _backgroundEnabledParam;
    ofImage _skyImage;
    ofMesh _skyMesh;
    
    ofImage _burner1Image;
    ofImage _burner2Image;
    ofMesh _burner1Mesh;
    ofMesh _burner2Mesh;
};

#endif 
