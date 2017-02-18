#include "bgshader.h"



const char* bgVertex = {
  "attribute vec3 in_position;\n"
  "varying vec3 pos;\n"

  "void main() {\n"
  "pos = in_position;\n"
  "gl_Position = vec4(in_position, 1.0);\n"
  "}\n"
};

const char* bgFrag = {

  "varying vec3 pos;\n"
  "uniform vec3 topColor;\n"
  "uniform vec3 bottomColor;\n"
  "void main()\n"
  "{\n"
  " gl_FragColor = vec4(mix(topColor, bottomColor, pos.y), 1.0);\n"
  "}\n"
};

BgShader::BgShader()
{
  compileProgram(bgVertex, bgFrag);

  _topColorId = glGetUniformLocation(_programId, "topColor");
  _bottomColorId = glGetUniformLocation(_programId, "bottomColor");
}

void BgShader::setUniform(const glm::vec3& topColor, const glm::vec3& bottomColor)
{
  glUniform3f(_topColorId, topColor.x, topColor.y, topColor.z);
  glUniform3f(_bottomColorId, bottomColor.x, bottomColor.y, bottomColor.z);
}
