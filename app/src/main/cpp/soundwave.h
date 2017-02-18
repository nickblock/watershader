//
// Created by nick on 18/02/17.
//

#ifndef WATERSHADER_SOUNDWAVE_H
#define WATERSHADER_SOUNDWAVE_H

#include "effect.h"
#include "heightmap.h"
#include "soundwaveshader.h"

class SoundwaveEffect : public Effect {
public:
  SoundwaveEffect();

  virtual void drawFrame();

protected:
  std::shared_ptr<SoundwaveShader> _shader;
  std::shared_ptr<HeightMap>      _heightMap;
};


#endif //WATERSHADER_SOUNDWAVE_H
