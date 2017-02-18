//
// Created by nick on 15/02/17.
//

#ifndef WATERSHADER_EFFECT_H
#define WATERSHADER_EFFECT_H

#include <memory>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Effect {

public:

  Effect();

  virtual void setScreen(int width, int height);

  virtual void drawFrame() = 0;

  virtual void touchMove(float x, float y) {};

protected:
  int _width, _height;


};


#endif //WATERSHADER_EFFECT_H
