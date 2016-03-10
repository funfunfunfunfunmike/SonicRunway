//
//  Buffer.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/8/16.
//
//

#ifndef SR_BUFFER_HPP
#define SR_BUFFER_HPP

#include <stdio.h>
#include <vector>

#include "Model.hpp"

//
// SrBuffer is a templated class that implements a circular buffer.
// It is intended to store a history of a given value and provide
// access to that value at some time in the past.
//
// Clients promise to Push new elements into the buffer at a specified
// frequency.  They can then access elements in the buffer by time.
//
template <class T>
class SrBuffer {
public:
    
    enum PushFrequency {
        OncePerAudioIn,
        OncePerUpdate
    };
    
    // Construct the buffer.  Clients are expected to call 'Push'
    // at the frequency designated by 'entriesPerSecond'.
    //
    // The buffer is circular -- any access beyond 'bufferSizeInSeconds'
    // is prohibited.
    SrBuffer(SrModel * model, PushFrequency freqency);
    virtual ~SrBuffer();
    
    // Push a new value into the buffer.  This should represent
    // the current value of the variable being stored.
    void Push(const T & value);
    
    // Access the value at some time in the past.  'age' must
    // be less than the total buffer size.  Values in the buffer
    // are interpolated or averaged given the filterWidth.
    T ComputeValue(float age, float filterWidthInSeconds) const;
    
    // Access the value at the given station index, assuming
    // that the buffer history corresponds to the speed of sound
    // along the runway as specified in the model.
    T ComputeValueAtStation(size_t stationIdx) const;
    
    // Access a specific element in the buffer by index.
    // Index 0 is the most recent element pushed onto the array.
    // Attempting to index beyond entriesInSeconds * sizeInSeconds
    // will crash.
    T operator[](size_t idx) const;
    
    // Return the fraction of a second per entry at the expected
    // rate.
    float GetSecondsPerEntry() const;
    
private:
    SrModel *_model;
    size_t _entriesPerSecond;
    std::vector<T> _values;
    size_t _idx;
};


template <class T>
SrBuffer<T>::SrBuffer(SrModel * model, PushFrequency frequency) :
    _model(model),
    _idx(0)
{
    if (frequency == OncePerAudioIn) {
        _entriesPerSecond = model->GetBuffersPerSecond();
    }
    if (frequency == OncePerUpdate) {
        _entriesPerSecond = model->GetFramesPerSecond();
    }
    
    _values.resize(_entriesPerSecond * model->GetMaxBufferDuration());
}

template <class T>
SrBuffer<T>::~SrBuffer()
{
    
}

template <class T>
void
SrBuffer<T>::Push(const T & value)
{
    if (_idx == 0) {
        _idx = _values.size();
    }
    _idx--;
    _values[_idx] = value;
}

template <class T>
T
SrBuffer<T>::operator[](size_t idx) const
{
    size_t i = (_idx + idx) % _values.size();
    return _values[i];
}

template <class T>
T
SrBuffer<T>::ComputeValue(float age, float filterWidth) const
{
    // XXX TODO:  implement filtering...
    
    int idx = age * _entriesPerSecond;
    return (*this)[idx];
}

typedef SrBuffer<float> SrFloatBuffer;

template <class T>
T
SrBuffer<T>::ComputeValueAtStation(size_t stationIdx) const
{
    float delayPerStation = _model->ComputeDelayPerStation();
    float age = delayPerStation * stationIdx;
    
    return ComputeValue(age, delayPerStation);
}

template <class T>
float
SrBuffer<T>::GetSecondsPerEntry() const
{
    return 1.0 / _entriesPerSecond;
}

#endif
