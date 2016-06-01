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

//
// Ui Mixin -- classes can derive from this and call
// _AddUI and _AddUIParameter to generate sliders, toggles,
// etc.
//
class SrUiMixin {
public:
    SrUiMixin(const std::string & name);
    virtual ~SrUiMixin();
    
    void SetUIPosition(float x, float y);
    ofxPanel * GetUiPanel() const;
    ofParameterGroup & GetParameterGroup();
    
protected:
    // Subclasses call this from their constructor to
    // Add UI elements to the panel for this pattern.
    void _AddUI(ofxBaseGui * item);
    
    template<typename T>
    void _AddUIParameter(ofParameter<T> & parameter) {
        _panel->add(parameter);
        _parameterGroup.add(parameter);
    }
    
private:
    ofxPanel * _panel;
    ofParameterGroup _parameterGroup;
};

#endif
