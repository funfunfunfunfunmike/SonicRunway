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
    SrUiMixin(name),
    _model(model),
    _audio(audio),
    _enabledBuffer(model),
    _enabledParam(true)
{
    printf("constructed pattern\n");
    _enabledToggle.setup(_enabledParam);
    _enabledParam.setName("Enabled");
    _AddUIParameter(_enabledParam);
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

void
SrPattern::SetEnabled(bool enabled)
{
    _enabledParam = enabled;
}

const SrFloatSimpleBuffer &
SrPattern::GetEnabled() const
{
    return _enabledBuffer;
}

void
SrPattern::Update()
{
    bool value = (bool) _enabledToggle;
    _enabledBuffer.Push((float) value);
    
    // Call subclass update
    _Update();
}

void
SrPattern::Draw()
{
    
    // Call subclass draw
    _Draw();
}
