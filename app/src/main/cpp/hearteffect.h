//
// Created by nick on 15/02/17.
//

#ifndef WATERSHADER_HEARTEFFECT_H
#define WATERSHADER_HEARTEFFECT_H

#include "effect.h"
#include "texture.h"
#include "heightmap.h"
#include "shader.h"

class HeartEffect : public Effect{

public:

  HeartEffect();

  virtual void drawFrame();

  virtual void touchMove(float x, float y);
protected:

  std::shared_ptr<Shader>     _shader;
  std::shared_ptr<HeightMap>  _heightMap;

  GLuint _timeId;
};


#endif //WATERSHADER_HEARTEFFECT_H
