//
//  OnsetDetect.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/11/16.
//
//

#include "OnsetDetect.hpp"
#include "Model.hpp"

SrOnsetDetect::SrOnsetDetect(SrModel * model) :
    _currentThreshold(0.3),
    _secondsSinceOnset(model, SrFloatBuffer::OncePerAudioIn),
    _threshold(model, SrFloatBuffer::OncePerAudioIn),
    _thresholdedNovelty(model, SrFloatBuffer::OncePerAudioIn),
    _novelty(model, SrFloatBuffer::OncePerAudioIn)
{
    int bufferSize = model->GetBufferSize();
    int hopSize = bufferSize / 2;
    _onset.setup("default", model->GetBufferSize(), hopSize,
                 model->GetSampleRate());
}

SrOnsetDetect::~SrOnsetDetect()
{
    // XXX delete _onset?  exit?
}

void
SrOnsetDetect::AudioIn(float * input, int bufferSize, int nChannels)
{
    _onset.audioIn(input, bufferSize, nChannels);
    
    SrTime now = std::chrono::system_clock::now();
    
    if (_onset.received()) {
        _timeOfLastOnset = now;
    }
    
    float secondsSinceOnset =
        SrFloatDuration(now - _timeOfLastOnset).count();
    _secondsSinceOnset.Push(secondsSinceOnset);
    _threshold.Push(_onset.threshold);
    _thresholdedNovelty.Push(_onset.thresholdedNovelty);
    _novelty.Push(_onset.novelty);
}

void
SrOnsetDetect::SetCurrentThreshold(float currentThreshold)
{
    _currentThreshold = currentThreshold;
}

SrTime
SrOnsetDetect::GetTimeOfLastOnset() const
{
    return _timeOfLastOnset;
}

const SrFloatBuffer &
SrOnsetDetect::GetSecondsSinceOnset() const
{
    return _secondsSinceOnset;
}
                            
const SrFloatBuffer &
SrOnsetDetect::GetThreshold() const
{
    return _threshold;
}

const SrFloatBuffer &
SrOnsetDetect::GetThresholdedNovelty() const
{
    return _thresholdedNovelty;
}

const SrFloatBuffer &
SrOnsetDetect::GetNovelty() const
{
    return _novelty;
}
