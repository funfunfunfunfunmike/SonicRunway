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
    UiMixin(name),
    _model(model),
    _audio(audio),
    _enabledBuffer(model, SrFrequencyOncePerUpdate),
    _enabledParam(true)
{
    printf("constructed pattern\n");
    _enabledToggle.setup(_enabledParam);
    _AddUI(&_enabledToggle);
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
