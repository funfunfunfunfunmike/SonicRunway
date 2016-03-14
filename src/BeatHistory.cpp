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
    _bpm(model, SrFrequencyOncePerAudioIn)
{
    int bufferSize = model->GetBufferSize();
    int hopSize = bufferSize / 2;
    int sampleRate = model->GetSampleRate();
    
    _beat.setup("default", bufferSize, hopSize, sampleRate);
}

SrBeatHistory::~SrBeatHistory()
{
    // XXX delete _beat?  .exit()?
}

void
SrBeatHistory::AudioIn(float * input, int bufferSize, int nChannels)
{
    _beat.audioIn(input, bufferSize, nChannels);
    
    _Push(_beat.received());
          
    _bpm.Push(_beat.bpm);
}

const SrFloatBuffer &
SrBeatHistory::GetBpm() const
{
    return _bpm;
}