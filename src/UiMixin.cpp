//
//  UIMixin.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/15/16.
//
//

#include "UIMixin.hpp"

UiMixin::UiMixin(const std::string & name)
{
    _panel.setup(name);
}

UiMixin::~UiMixin()
{
    
}

void
UiMixin::DrawUI()
{
    _panel.draw();
}
    
void
UiMixin::SetUIPosition(float x, float y)
{
    _panel.setPosition(x, y);
}
    
void
UiMixin::_AddUI(ofxBaseGui * item)
{
    _panel.add(item);
}
