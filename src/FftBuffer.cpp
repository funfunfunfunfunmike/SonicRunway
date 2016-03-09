//
//  FftBuffer.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/6/16.
//
//

#include "FftBuffer.hpp"
#include "Model.hpp"
#include "Audio.hpp"

SrFftBuffer::SrFftBuffer(SrModel * model,
                         SrAudio * audio) :
    _model(model),
    _audio(audio),
    _xPos(0)
{
    float maxDuration = _model->GetMaxBufferDuration();
    int width = maxDuration * _model->GetBuffersPerSecond();
    int numBands = _audio->GetNumMelBands();
    
    _rollingBuffer.allocate(width, numBands, 1);
    _outputBuffer.allocate(width, numBands, 1);
    float perStationWidth = (float) maxDuration / _model->ComputeDelayPerStation();
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
    
    int numBands = _audio->GetNumMelBands();
    for(int i = 0; i < numBands; i++) {
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
