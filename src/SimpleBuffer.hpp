//
//  SimpleBuffer.h
//  SonicRunway
//
//  Created by Rob Jensen on 5/5/16.
//
//

#ifndef SR_SIMPLE_BUFFER_HPP
#define SR_SIMPLE_BUFFER_HPP

#include <stdio.h>
#include <vector>

#include "Model.hpp"
#include "Types.hpp"

//
// SrSimpleBuffer is a templated class that implements a circular buffer.
// It is intended to store a history of a given value for every
// frame, and provide access to that value at each gate.
//
// Clients Push new elements into the buffer once per frame.
// They can then access elements in the buffer by gate index.
//
// XXX currently only using Float -- maybe the template is overkill?
//
template <class T>
class SrSimpleBuffer {
public:
    
    // Construct the buffer.  Clients are expected to call 'Push'
    // once per frame.
    //
    // The buffer is circular -- any access beyond 'bufferSizeInSeconds'
    // is prohibited.
    SrSimpleBuffer(SrModel * model);
    virtual ~SrSimpleBuffer();
    
    // Push a new value into the buffer.  This should represent
    // the current value of the variable being stored.
    void Push(const T & value);
    
    // Access the value at the given gate index, assuming
    // that the buffer history corresponds to the speed of sound
    // along the runway as specified in the model.
    T GetValueAtGate(size_t gateIdx) const;
    
    // Access a specific element in the buffer by index.
    // Index 0 is the most recent element pushed onto the array.
    // Attempting to index >= entriesInSeconds * sizeInSeconds
    // will crash.
    T operator[](size_t idx) const;
    
private:
    SrModel *_model;
    std::vector<T> _values;
    size_t _idx;
};

// Define some typedefs for convenience
typedef SrSimpleBuffer<float> SrFloatSimpleBuffer;
typedef SrSimpleBuffer<float> SrIntSimpleBuffer;

template <class T>
SrSimpleBuffer<T>::SrSimpleBuffer(SrModel * model) :
    _model(model),
    _idx(0)
{
    _values.resize(model->ComputeFramesPerSecond()
                   * model->GetMaxBufferDuration());
}

template <class T>
SrSimpleBuffer<T>::~SrSimpleBuffer()
{
    
}

template <class T>
void
SrSimpleBuffer<T>::Push(const T & value)
{
    if (_idx == 0) {
        _idx = _values.size();
    }
    _idx--;
    _values[_idx] = value;
}

template <class T>
T
SrSimpleBuffer<T>::operator[](size_t idx) const
{
    size_t i = (_idx + idx) % _values.size();
    return _values[i];
}

template <class T>
T
SrSimpleBuffer<T>::GetValueAtGate(size_t gateIdx) const
{
    return (*this)[gateIdx * _model->GetFramesPerGate()];
}

#endif
