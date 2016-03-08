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
                         int framesPerSecond,
                         float delayPerStation) :
    _numBands(numBands),
    _sampleRate(sampleRate),
    _bufferSize(bufferSize),
    _framesPerSecond(framesPerSecond),
    _buffersPerSecond((float) _sampleRate / _bufferSize),
    _xPos(0),
    _bufferLengthInSeconds(4.0),
    _delayPerStation(delayPerStation)
{
    int width = _bufferLengthInSeconds * _buffersPerSecond;
    
    _rollingBuffer.allocate(width, numBands, 1);
    _outputBuffer.allocate(width, numBands, 1);
    float perStationWidth = (float) _bufferLengthInSeconds / _delayPerStation;
    printf("delay per station %f, perStationWidth %f\n",
           _delayPerStation, perStationWidth);
    _perStationBuffer.allocate(perStationWidth, numBands, 1);
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
        _rollingBuffer.setColor(_xPos, i, ofColor(energy * 255));
    }
}

void
SrFftBuffer::Update()
{
    // XXX this is all a big hacky attempt to rescale the outputbuffer
    // into something that is the size of the _perStationBuffer.
    // It would be better to use some openframeworks scale operation,
    // but ofPixels.resize() didn't seem to work...
    
    float xScale = (float) _perStationBuffer.getWidth() /
                           _outputBuffer.getWidth();
    
    for(int x = 0; x < _perStationBuffer.getWidth(); x++) {
        for(int y = 0; y < _perStationBuffer.getHeight(); y++) {
            _perStationBuffer.setColor(x,y,ofFloatColor(0.0));
        }
    }
    
    for(int x = 0; x < _outputBuffer.getWidth(); x++) {
        int thisX = (x + _xPos) % _rollingBuffer.getWidth();
        
        int floorX = floor(x * xScale);
        int ceilX = ceil(x * xScale);
        if (ceilX >= _perStationBuffer.getWidth()) {
            ceilX = _perStationBuffer.getWidth() - 1;
        }
        
        float t = fmod(x * xScale, 1.0);
        
        for(int y = 0; y < _outputBuffer.getHeight(); y++) {
            ofFloatColor c(_rollingBuffer.getColor(thisX,y));
            _outputBuffer.setColor(x, y, c);
            
            ofFloatColor floorCol = _perStationBuffer.getColor(floorX, y);
            ofFloatColor ceilCol = _perStationBuffer.getColor(ceilX, y);
            
            floorCol += c * (1.0 - t);
            ceilCol += c * t;
            
            _perStationBuffer.setColor(floorX, y, floorCol);
            _perStationBuffer.setColor(ceilX, y, ceilCol);
        }
    }
}

void
SrFftBuffer::Draw(float x, float y, float width, float height) const
{
    ofImage image;
    
    // XXX move this allocation to constructor to avoid re-allocating?
    /*
    image.allocate(_outputBuffer.getWidth(),
                   _outputBuffer.getHeight(),
                   OF_IMAGE_GRAYSCALE);
    image.setFromPixels(_outputBuffer);
    image.draw(x, y, width, height);
     */
    
    image.allocate(_perStationBuffer.getWidth(),
                   _perStationBuffer.getHeight(),
                   OF_IMAGE_GRAYSCALE);
    image.setFromPixels(_perStationBuffer);
    image.draw(x, y);
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

const ofFloatPixels &
SrFftBuffer::GetPerStationData() const
{
    return _perStationBuffer;
}

float
SrFftBuffer::GetBufferLengthInSeconds() const
{
    return _bufferLengthInSeconds;
}