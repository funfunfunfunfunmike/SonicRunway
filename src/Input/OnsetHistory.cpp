//
//  OnsetHistory.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/11/16.
//
//

#include "OnsetHistory.hpp"
#include "Model.hpp"

SrOnsetHistory::SrOnsetHistory(SrModel * model) :
    SrEventHistory(model, SrFrequencyOncePerAudioIn),
    _gotOnset(false),
    _currentThreshold(0.3),
    _threshold(model, SrFrequencyOncePerAudioIn),
    _thresholdedNovelty(model, SrFrequencyOncePerAudioIn),
    _novelty(model, SrFrequencyOncePerAudioIn)
{
    int bufferSize = model->GetBufferSize();
    int hopSize = bufferSize / 2;
    _onset.setup("default", model->GetBufferSize(), hopSize,
                 model->GetSampleRate());
    
    // Set up listener for onset event
    ofAddListener(_onset.gotOnset, this, &SrOnsetHistory::_OnOnsetEvent);
}

SrOnsetHistory::~SrOnsetHistory()
{
    // XXX delete _onset?  exit?
}

void
SrOnsetHistory::_OnOnsetEvent(float & time)
{
    _gotOnset = true;
}

void
SrOnsetHistory::AudioIn(float * input, int bufferSize, int nChannels)
{
    _onset.audioIn(input, bufferSize, nChannels);
    
    // Push the current value
    _Push(_gotOnset);
    
    // Reset the flag
    _gotOnset = false;
    
    _threshold.Push(_onset.threshold);
    _thresholdedNovelty.Push(_onset.thresholdedNovelty);
    _novelty.Push(_onset.novelty);
}

void
SrOnsetHistory::SetCurrentThreshold(float currentThreshold)
{
    _currentThreshold = currentThreshold;
}

const SrFloatBuffer &
SrOnsetHistory::GetThreshold() const
{
    return _threshold;
}

const SrFloatBuffer &
SrOnsetHistory::GetThresholdedNovelty() const
{
    return _thresholdedNovelty;
}

const SrFloatBuffer &
SrOnsetHistory::GetNovelty() const
{
    return _novelty;
}
