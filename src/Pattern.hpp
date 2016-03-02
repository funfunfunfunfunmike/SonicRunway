//
//  Pattern.hpp
//  SonicRunway
//
//  Created by Rob Jensen on 3/2/16.
//
//

#ifndef SR_PATTERN_HPP
#define SR_PATTERN_HPP

#include <stdio.h>

#include "Types.hpp"

class SrModel;
class SrAudio;

class SrPattern {
public:
    SrPattern(SrModel * model, SrAudio * audio);
    virtual ~SrPattern();
    
    virtual void Update(const SrTime & now) = 0;
    virtual void Draw(const SrTime & now) const = 0;
    
    SrModel * GetModel() const;
    SrAudio * GetAudio() const;
    
private:
    SrModel *_model;
    SrAudio *_audio;
};

#endif
