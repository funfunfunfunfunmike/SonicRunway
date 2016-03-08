//
//  FftBuffer.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/6/16.
//
//

#include "FftBuffer.hpp"
#include "Model.hpp"

SrFftBuffer::SrFftBuffer(int numBands,
                         int sampleRate, int bufferSize,
                         int framesPerSecond) :
    _numBands(numBands),
    _sampleRate(sampleRate),
    _bufferSize(bufferSize),
    _framesPerSecond(framesPerSecond),
    _buffersPerSecond((float) _sampleRate / _bufferSize),
    _xPos(0),
    _bufferLengthInSeconds(4.0)
{
    int width = _bufferLengthInSeconds * _buffersPerSecond;
    
    _rollingBuffer.allocate(width, numBands, 1);
    _outputBuffer.allocate(width, numBands, 1);
}

SrFftBuffer::~SrFftBuffer()
{
    
}

void
SrFftBuffer::FftIn(float * energies)
{
    // decrement the position we are drawing to, and wrap
    // around the width
    _xPos--;
    if (_xPos < 0) {
        _xPos = _rollingBuffer.getWidth() - 1;
    }
    
    for(int i = 0; i < _numBands; i++) {
        float energy = energies[i];
        //_rollingBuffer.setColor(_xPos, i, ofColor(energy * 255));
        _rollingBuffer.setColor(_xPos, i, ofColor(energy * 255));
    }
}

void
SrFftBuffer::Update()
{
    for(int x = 0; x < _outputBuffer.getWidth(); x++) {
        int thisX = (x + _xPos) % _rollingBuffer.getWidth();
        for(int y = 0; y < _outputBuffer.getHeight(); y++) {
            _outputBuffer.setColor(x, y, _rollingBuffer.getColor(thisX,y));
        }
    }
}

void
SrFftBuffer::Draw(float x, float y, float width, float height) const
{
    ofImage image;
    
    // XXX move this allocation to constructor to avoid re-allocating?
    image.allocate(_outputBuffer.getWidth(),
                   _outputBuffer.getHeight(),
                   OF_IMAGE_GRAYSCALE);
    image.setFromPixels(_outputBuffer);
    image.draw(x, y, width, height);
}

float
SrFftBuffer::GetBuffersPerSecond() const
{
    return _buffersPerSecond;
}

const ofFloatPixels &
SrFftBuffer::GetData() const
{
    return _outputBuffer;
}

float
SrFftBuffer::GetBufferLengthInSeconds() const
{
    return _bufferLengthInSeconds;
}