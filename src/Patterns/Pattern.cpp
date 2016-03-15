//
//  Pattern.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/2/16.
//
//

#include "Pattern.hpp"
#include "Model.hpp"
#include "Audio.hpp"

SrPattern::SrPattern(const std::string & name,
                     SrModel * model,
                     SrAudio * audio) :
    _model(model),
    _audio(audio),
    _enabledBuffer(model, SrFrequencyOncePerUpdate),
    _enabledParam(true)
{
    _panel.setup(name);
    _enabledToggle.setup(_enabledParam);
    _AddUI(&_enabledToggle);
    printf("constructed pattern\n");
}

SrPattern::~SrPattern()
{
    printf("destroyed pattern\n");
}

SrModel *
SrPattern::GetModel() const
{
    return _model;
}

SrAudio *
SrPattern::GetAudio() const
{
    return _audio;
}

const SrFloatBuffer &
SrPattern::GetEnabled() const
{
    return _enabledBuffer;
}

void
SrPattern::SetUIPosition(float x, float y)
{
    _panel.setPosition(x, y);
}

void
SrPattern::Update(const SrTime & now)
{
    bool value = (bool) _enabledToggle;
    printf("value %d\n", value);
    _enabledBuffer.Push((float) value);
    
    // Call subclass update
    _Update(now);
}

void
SrPattern::Draw(const SrTime & now)
{
    
    // Call subclass draw
    _Draw(now);
}

void
SrPattern::DrawUI()
{
    _panel.draw();
}

void
SrPattern::_AddUI(ofxBaseGui * item)
{
    _panel.add(item);
}