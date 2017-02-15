//
// Created by nick on 15/02/17.
//

#ifndef WATERSHADER_WATERAPP_H
#define WATERSHADER_WATERAPP_H

#include "effect.h"
#include "watershader.h"
#include "texture.h"
#include "heightmap.h"

#include <glm/vec3.hpp>

#include <memory>

class WaterEffect : public Effect {

public:
  WaterEffect(const ImageDataList&);

  virtual void setScreen(int width, int height);

  virtual void drawFrame();

  virtual void touchMove(float x, float y);

protected:

  std::shared_ptr<WaterShader>    _waterShader;
  std::shared_ptr<CubeMap>        _cubeMap;
  std::shared_ptr<Texture>        _texture;
  std::shared_ptr<HeightMap>      _heightMap;


  glm::vec3 _eyePos;
  glm::vec3 _mousePos;
  float     _eyeDist;
  int       _width, _height;
};


#endif //WATERSHADER_WATERAPP_H
