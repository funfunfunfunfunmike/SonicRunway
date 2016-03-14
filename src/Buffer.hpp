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
#include "Types.hpp"

//
// SrBuffer is a templated class that implements a circular buffer.
// It is intended to store a history of a given value and provide
// filtered access to that value at some time in the past.
//
// Clients promise to Push new elements into the buffer at a specified
// frequency.  They can then access elements in the buffer by time.
// For convenience, the buffer is initialized with the SrModel, so
// it can provide values relative to a given station given the
// delay of the speed of sound.
//
// XXX currently only using Float -- maybe the template is overkill?
//
template <class T>
class SrBuffer {
public:
    
    // Construct the buffer.  Clients are expected to call 'Push'
    // at the frequency designated by 'entriesPerSecond'.
    //
    // The buffer is circular -- any access beyond 'bufferSizeInSeconds'
    // is prohibited.
    SrBuffer(SrModel * model, SrFrequency freqency);
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
    // Attempting to index >= entriesInSeconds * sizeInSeconds
    // will crash.
    T operator[](size_t idx) const;
    
    // Return the fraction of a second per entry at the expected
    // rate.
    float GetSecondsPerEntry() const;
    
private:
    SrModel *_model;
    float _entriesPerSecond;
    std::vector<T> _values;
    size_t _idx;
};

// Define some typedefs for convenience
typedef SrBuffer<float> SrFloatBuffer;
typedef SrBuffer<float> SrIntBuffer;

template <class T>
SrBuffer<T>::SrBuffer(SrModel * model, SrFrequency frequency) :
    _model(model),
    _idx(0)
{
    if (frequency == SrFrequencyOncePerAudioIn) {
        _entriesPerSecond = model->GetBuffersPerSecond();
    }
    if (frequency == SrFrequencyOncePerUpdate) {
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
SrBuffer<T>::ComputeValue(float age, float filterWidthInSeconds) const
{
    // XXX averaging and interpolating imposes some requirements on templated
    // class.  May require some work to generalize..
    
    float floatIdx = age * _entriesPerSecond;
    float windowSize = filterWidthInSeconds / GetSecondsPerEntry();
    
    // If the desired filter width is less than the width of the buffer,
    // then linearly interpolate the neighboring entries.
    if (windowSize < 1.0) {
        int minIdx = floor(floatIdx);
        int maxIdx = ceil(floatIdx);
        float t = fmod(floatIdx, 1.0);
       
        T a = (*this)[minIdx];
        T b = (*this)[maxIdx];
        return (1.0 - t) * a + t * b;
    }
    
    // Otherwise, average the samples inside the filter region.
    // XXX this should really do some kind of gaussian filter...
    int minIdx = (int) floatIdx - windowSize / 2;
    int maxIdx = (int) floatIdx + windowSize / 2;
    
    if (minIdx < 0) {
        minIdx = 0;
    }
    
    T sum = 0;
    for(int i = minIdx; i <= maxIdx; i++) {
        sum += (*this)[i];
    }
    
    return sum / (maxIdx - minIdx + 1);
}

template <class T>
T
SrBuffer<T>::ComputeValueAtStation(size_t stationIdx) const
{
    float delayPerStation = _model->ComputeDelayPerStation();
    float age = delayPerStation * stationIdx;
    
    float filterWidthInSeconds = delayPerStation;
    return ComputeValue(age, filterWidthInSeconds);
}

template <class T>
float
SrBuffer<T>::GetSecondsPerEntry() const
{
    return 1.0 / _entriesPerSecond;
}

#endif
