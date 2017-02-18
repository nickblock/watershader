//
// Created by nick on 15/02/17.
//

#include "heartshader.h"



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
  "vec3 normPos = vec3(pos.xy + vec2(0.5, 0.5), 1.0);\n"

  "vec2 p = 4.0 * (normPos.xy);\n"
  "vec2 p2 = 45.0 * (normPos.xy);\n"
  "\n"
  "vec3 col = vec3(0.0, 0.0, 0.0);\n"
  "vec3 col1 = mix(vec3(1.0,0.0,0.6), vec3(1.0,0.0,0.4), sqrt(p.y));\n"
  "vec3 col2 = mix(vec3(1.0,0.0,0.1), vec3(1.0,0.1,0.0), pow(p.y, 1.3));\n"
  "\n"
  "float x = p.x - 2.0;\n"
  "float y = p.y - 1.65;\n"
  
  "col = paintSpecialHeart(col, col1, x, y);\n"
  "\n"
  "gl_FragColor = vec4(col, max(col.r, max(col.g, col.b)));\n"
  "}\n"
};


HeartShader::HeartShader()
{
  compileProgram(heartVertex, heartFrag);

  _timeId = glGetUniformLocation(_programId, "time");
}


void HeartShader::setUniform(float time)
{
  glUniform1f(_timeId, time);
}
