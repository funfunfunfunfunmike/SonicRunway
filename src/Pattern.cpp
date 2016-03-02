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

SrPattern::SrPattern(SrModel * model, SrAudio * audio) :
    _model(model),
    _audio(audio)
{
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