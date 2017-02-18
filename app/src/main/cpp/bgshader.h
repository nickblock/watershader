#ifndef BG_SHADER_H
#define BG_SHADER_H

#include "shader.h"

class BgShader : public Shader
{
public:
  BgShader();

  void setUniform(const glm::vec3& topColor, const glm::vec3& bottomColor);
protected:

  GLuint _topColorId;
  GLuint _bottomColorId;

};

#endif
