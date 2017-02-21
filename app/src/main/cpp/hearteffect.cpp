 //
// Created by nick on 15/02/17.
//

#include "hearteffect.h"
#include "app.h"

const char* heartVertex = {
  "attribute vec3 in_position;\n"
  "varying vec3 pos;\n"

  "void main() {\n"
  "pos = in_position;\n"
  "gl_Position = vec4(in_position, 1.0);\n"
  "}\n"
};

const char* heartFrag = {

  "varying vec3 pos;\n"
#ifdef DESKTOP_BUILD
  "uniform float time;\n"
#else
  "uniform highp float time;\n"
#endif
  "vec3 paintHeart(vec3 col, vec3 col1, float x, float y)\n"
  "{\n"
  "  float r = x*x + pow((y - pow(x*x, 1.0/3.0)), 2.0);\n"
  "  r -= pow(sin(time), 10.0);\n"
  "  \n"
  "  if (r < 1.5) {\n"
  "    col = col1 * r;\n"
  "  }\n"
  "  return col;\n"
  "}\n"
  "\n"
  "vec3 paintSpecialHeart(vec3 col, vec3 col1, float x, float y)\n"
  "{\n"
  "  float r = x*x + pow((y - pow(x*x, 1.0/3.0)), 2.0);\n"
  "    r -= sin(time) - 0.6;\n"
  "    if ((r < 2.0 && r > 1.5) || (r < 1.0 && r > 0.6) || (r < 0.3 && r > 0.0)) {\n"
  "    col = col1 * r * 1.5*(sin(time)+1.0);\n"
  "    //col = col1 * r * 3.0;\n"
  "    }\n"
  "  return col;\n"
  "}\n"

  "void main() {\n"
  "vec2 normPos = 0.5*pos.xy + vec2(0.5, 0.5);\n"

  "vec2 p = 4.0 * (normPos.xy);\n"
  "vec2 p2 = 45.0 * (normPos.xy);\n"
  "\n"
  "vec3 col = vec3(0.0, 0.0, 0.0);\n"
  "vec3 col1 = mix(vec3(1.0,1.0,1.0), vec3(1.0,1.0,1.0), sqrt(p.y));\n"
  "vec3 col2 = mix(vec3(1.0,1.0,1.0), vec3(1.0,1.0,1.0), pow(p.y, 1.3));\n"
  "\n"
  "float x = p.x - 2.0;\n"
  "float y = p.y - 1.65;\n"
  
  "col = paintSpecialHeart(col, col1, x, y);\n"
  "\n"
  "gl_FragColor = vec4(1.0, 1.0, 1.0, col.r);\n"
  "}\n"
};


HeartEffect::HeartEffect()
{
  _shader = std::make_shared<Shader>();

  _shader->compileProgram(heartVertex, heartFrag);

  _timeId = glGetUniformLocation(_shader->id(), "time");

  _heightMap = std::make_shared<HeightMap>(1);
}

void HeartEffect::drawFrame()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _shader->use();
  glUniform1f(_timeId, App::getTime());

  //draw grid usng shder
  _heightMap->draw(_shader->getPosAttr());

  glDisable(GL_BLEND);
}

void HeartEffect::touchMove(float x, float y)
{

}
