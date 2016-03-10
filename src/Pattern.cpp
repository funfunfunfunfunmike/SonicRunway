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
    _audio(audio)
{
    _panel.setup(name);
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

void
SrPattern::SetUIPosition(float x, float y)
{
    _panel.setPosition(x, y);
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