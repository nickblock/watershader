#ifndef SMOKE_EFFECT_H
#define SMOKE_EFFECT_H

#include "effect.h"
#include "shader.h"
#include "heightmap.h"
#include "framebuffer.h"

class SmokeEffect : public Effect
{
public:
  SmokeEffect(int width, int height);  

  virtual void setScreen(int width, int height);
  virtual void touchMove(float x, float y);
  virtual void drawFrame();

protected:

  std::shared_ptr<Shader>      _smokeShader;
  std::shared_ptr<Shader>      _finalShader;
  std::shared_ptr<HeightMap>   _heightMap;
  std::shared_ptr<FrameBuffer> _texture[2];

  GLuint _resId;
  GLuint _smokeSourceId;
  GLuint _timeId;

  bool _flipFlop;

  glm::vec2 _mousePos;
};

#endif