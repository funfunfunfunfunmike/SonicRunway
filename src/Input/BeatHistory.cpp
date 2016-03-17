//
//  BeatHistory.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/14/16.
//
//

#include "BeatHistory.hpp"
#include "Model.hpp"

SrBeatHistory::SrBeatHistory(SrModel * model) :
    SrEventHistory(model, SrFrequencyOncePerAudioIn),
    _bpm(model, SrFrequencyOncePerAudioIn),
    _gotBeat(false)
{
    int bufferSize = model->GetBufferSize();
    int hopSize = bufferSize / 2;
    int sampleRate = model->GetSampleRate();
    
    _beat.setup("default", bufferSize, hopSize, sampleRate);
    
    // Set up listener for beat event
    ofAddListener(_beat.gotBeat, this, &SrBeatHistory::_OnBeatEvent);
}

SrBeatHistory::~SrBeatHistory()
{
    // XXX delete _beat?  .exit()?
}

void
SrBeatHistory::_OnBeatEvent(float & time)
{
    _gotBeat = true;
}

void
SrBeatHistory::AudioIn(float * input, int bufferSize, int nChannels)
{
    _beat.audioIn(input, bufferSize, nChannels);
    
    // Push the current beat
    _Push(_gotBeat);
    
    // Reset the flag
    _gotBeat = false;
          
    _bpm.Push(_beat.bpm);
}

const SrFloatBuffer &
SrBeatHistory::GetBpm() const
{
    return _bpm;
}