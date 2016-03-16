//
//  FftPattern.cpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/4/16.
//
//

#include "FftPattern.hpp"
#include "Audio.hpp"
#include "Model.hpp"

SrFftPattern::SrFftPattern(const std::string & name,
                           SrModel * model, SrAudio * audio) :
    SrPattern(name, model, audio),
    _hueShiftParam(0.0),
    _hueShiftBuffer(model, SrFrequencyOncePerUpdate)
{
    _pixels.allocate(GetModel()->GetNumStations(),
                     GetAudio()->GetFfts().size(), 3);
    
    _hueShiftParam.setName("Hue Shift");
    _hueShiftParam.setMin(0.0);
    _hueShiftParam.setMax(1.0);
    
    _AddUIParameter(_hueShiftParam);
    
    _hueShiftBuffer.Push((float) _hueShiftParam);
}

SrFftPattern::~SrFftPattern()
{
    
}

void
SrFftPattern::_Update(const SrTime & now)
{
    const SrModel * model = GetModel();
    
    // XXX disabled for now..
    //_hueShiftBuffer.Push(_hueShiftBuffer[0] + 0.0025);
    //_hueShiftBuffer.Push(_hueShiftBuffer[0] + 0.005);
    _hueShiftBuffer.Push((float) _hueShiftParam);
    
    const vector<SrFloatBuffer> & ffts = GetAudio()->GetFfts();
    
    for(int station = 0; station < model->GetNumStations(); station++) {
        float enabled = GetEnabled().ComputeValueAtStation(station);
        float hueShift =
            _hueShiftBuffer.ComputeValueAtStation(station);
        
        for(int band = 0; band < ffts.size(); band++) {
            if (not enabled) {
                _pixels.setColor(station, band, ofColor(0.0,0.0,0.0));
                continue;
            }
            
            float fftValue = ffts[band].ComputeValueAtStation(station);
            
            ofFloatColor c;
            float baseColor = 0.15 + hueShift;
            float hue = baseColor - 0.6 * (1.0 - fftValue);
            if (hue < 0.0) {
                hue += 1.0;
            }
            hue = fmod(hue, 1.0);
            c.setHsb(hue, 1.0, fftValue * 2.0);
            
            _pixels.setColor(station,band,c);
        }
    }
}

void
SrFftPattern::_Draw(const SrTime & now) const
{
    ofSetColor(255.0,255.0,255.0,255.0);
    
    int lightsPerStation = GetModel()->GetLightsPerStation();
    
    float scaledWidth = GetModel()->GetMaxBufferDuration() /
                        GetModel()->ComputeDelayPerStation();
    
    ofImage image;
    // XXX move this allocation to constructor to avoid re-allocating?
    image.allocate(_pixels.getWidth(), _pixels.getHeight(), OF_IMAGE_COLOR);
    
    image.setFromPixels(_pixels);
    
    image.draw(0,0,_pixels.getWidth(), lightsPerStation * 1.5);
    
    ofPushMatrix();
    ofTranslate(0,GetModel()->GetLightsPerStation());
    ofScale(1,-1);
    
    image.draw(0,0,_pixels.getWidth(), lightsPerStation * 1.5);
    ofPopMatrix();
}
