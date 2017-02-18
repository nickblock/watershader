//
// Created by nick on 15/02/17.
//

#ifndef WATERSHADER_HEARTSHADER_H
#define WATERSHADER_HEARTSHADER_H


#include "shader.h"

class HeartShader : public Shader{
  
public:
  HeartShader();

  void setUniform(int width, int height, float time);

protected:

  GLuint _timeId;
};


#endif //WATERSHADER_HEARTSHADER_H
