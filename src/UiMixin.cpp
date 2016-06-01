//
//  UIMixin.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/15/16.
//
//

#include "UIMixin.hpp"

SrUiMixin::SrUiMixin(const std::string & name)
{
    _panel = new ofxPanel();
    _panel->setup(name);
    _parameterGroup.setName(name);
}

SrUiMixin::~SrUiMixin()
{
    // XXX should delete, but need to figure out how
    // to cleanly unwind the ui structures.
    //delete _panel;
}

ofxPanel *
SrUiMixin::GetUiPanel() const
{
    return _panel;
}

void
SrUiMixin::SetUIPosition(float x, float y)
{
    _panel->setPosition(x, y);
}
    
void
SrUiMixin::_AddUI(ofxBaseGui * item)
{
    _panel->add(item);
}

ofParameterGroup &
SrUiMixin::GetParameterGroup()
{
    return _parameterGroup;
}
