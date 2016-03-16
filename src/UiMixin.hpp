//
//  UIMixin.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/15/16.
//
//

#ifndef SR_UI_MIXIN_HPP
#define SR_UI_MIXIN_HPP

#include <stdio.h>
#include "ofxGui.h"

class UiMixin {
public:
    UiMixin(const std::string & name);
    virtual ~UiMixin();
    
    void SetUIPosition(float x, float y);
    void DrawUI();
    
protected:
    // Subclasses call this from their constructor to
    // Add UI elements to the panel for this pattern.
    void _AddUI(ofxBaseGui * item);
    
    template<typename T>
    void _AddParameter(ofParameter<T> & parameter) {
        _panel.add(parameter);
    }
    
private:
    ofxPanel _panel;
};

#endif
