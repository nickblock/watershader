//
// Created by nick on 18/02/17.
//

#ifndef WATERSHADER_SOUNDWAVE_H
#define WATERSHADER_SOUNDWAVE_H

#include "effect.h"
#include "heightmap.h"
#include "shader.h"

class SoundwaveEffect : public Effect {
public:
  SoundwaveEffect();

  virtual void drawFrame();

protected:
  std::shared_ptr<Shader>     _shader;
  std::shared_ptr<HeightMap>  _heightMap;

  GLuint _timeId;
  GLuint _pixelWidthId;
  GLuint _pixelHeightId;

};


#endif //WATERSHADER_SOUNDWAVE_H
