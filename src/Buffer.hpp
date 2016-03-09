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
    // Construct the buffer.  Clients are expected to call 'Push'
    // at the frequency designated by 'entriesPerSecond'.
    //
    // The buffer is circular -- any access beyond 'bufferSizeInSeconds'
    // is prohibited.
    SrBuffer(size_t entriesPerSecond, float sizeInSeconds);
    virtual ~SrBuffer();
    
    // Push a new value into the buffer.  This should represent
    // the current value of the variable being stored.
    void Push(const T & value);
    
    // Access the value at some time in the past.  'age' must
    // be less than the total buffer size.  Values in the buffer
    // are interpolated or averaged given the filterWidth.
    T ComputeValue(float age, float filterWidthInSeconds) const;
    
    // Access a specific element in the buffer by index.
    // Index 0 is the most recent element pushed onto the array.
    // Attempting to index beyond entriesInSeconds * sizeInSeconds
    // will crash.
    T operator[](size_t idx) const;
    
private:
    size_t _entriesPerSecond;
    std::vector<T> _values;
    size_t _idx;
};


template <class T>
SrBuffer<T>::SrBuffer(size_t entriesPerSecond, float sizeInSeconds) :
    _entriesPerSecond(entriesPerSecond),
    _values(entriesPerSecond * sizeInSeconds),
    _idx(0)
{
    
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
    int idx = age * _entriesPerSecond;
    return (*this)[idx];
}

typedef SrBuffer<float> SrFloatBuffer;

#endif
