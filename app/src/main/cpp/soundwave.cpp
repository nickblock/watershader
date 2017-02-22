//
// Created by nick on 18/02/17.
//

#include "soundwave.h"
#include "app.h"


const char* soundVertex = {
  "attribute vec3 in_position;\n"
  "varying vec3 pos;\n"

  "void main() {\n"
  "pos = in_position;\n"
  "gl_Position = vec4(in_position, 1.0);\n"
  "}\n"
};

const char* soundFrag = {

"varying vec3 pos;\n"
#ifdef DESKTOP_BUILD
"uniform float time;\n"
#else
"uniform highp float time;\n"
#endif

"uniform float lineWidths[4];\n"
"uniform float amplitudes[4];\n"

"float iChannel = 0.5;\n"
"float squared(float value) { return value * value; }\n"
"float getAmp(float frequency) { return iChannel; }\n"
"float getWeight(float f) {\n"
"    return (+ getAmp(f-2.0) + getAmp(f-1.0) + getAmp(f+2.0) + getAmp(f+1.0) + getAmp(f)) / 5.0;\n"
"}\n"
"vec3 quantize(vec3 c, float num)\n"
"{\n"
" return floor((c/num)*10.0)*num/10.0;\n"
"}\n"
"float quantize(float c, float num)\n"
"{\n"
" return floor((c/num)*10.0)*num/10.0;\n"
"}\n"
""
"void main() {\n"

"  float freq = 3.0;\n"
"  vec2 uvTrue = 0.5*pos.xy + vec2(0.5, 0.5);\n"
"  vec2 uv = -1.0 + 2.0 * uvTrue;\n"
"  float curve = sin((uv.x + time)*freq);\n"
"  vec3 color = vec3(1.0);\n"
"  float tr = 0.0f;\n"
"  for(int i=0; i<4; i++) {\n"
"    float thisCurve = curve * amplitudes[i];\n"
"    tr += thisCurve > uv.y - lineWidths[i] &&  thisCurve < uv.y + lineWidths[i] ? 1.0 : 0.0;\n"
"  }\n"
"  gl_FragColor = vec4(color, tr);\n"
"}\n"


/*
"void main()\n"
"{\n"
"  vec2 uvTrue = pos.xy + vec2(0.5, 0.5);\n"
"  vec2 uv = -1.0 + 2.0 * uvTrue;\n"
"\n"
"  float lineIntensity;\n"
"  float glowWidth;\n"
"  vec3 color = vec3(0.0);\n"
"    \n"
"  for(float i = 0.0; i < 5.0; i++) {\n"
"        \n"
"    uv.y += (0.2 * sin(uv.x + i/7.0 - time * 0.6));\n"
"    float Y = uv.y + getWeight(squared(i) * 20.0) *iChannel;\n"
"    lineIntensity = 0.4 + squared(1.6 * abs(mod(uvTrue.x + i / 1.3 + time,2.0) - 1.0));\n"
"    glowWidth = abs(lineIntensity / (150.0 * Y));\n"
"    color += vec3(glowWidth * (2.0 + sin(time * 0.13)),\n"
"                      glowWidth * (2.0 - sin(time * 0.23)),\n"
"                      glowWidth * (2.0 - cos(time * 0.19)));\n"
"  } \n"
"  \n"
//"  color = quantize(color,3.0);"
"  gl_FragColor = vec4(color, max(color.r, max(color.g, color.b)));\n"
"}\n"
*/
};

SoundwaveEffect::SoundwaveEffect()
{

  _shader = std::make_shared<Shader>();
  _shader->compileProgram(soundVertex, soundFrag);

  _timeId = glGetUniformLocation(_shader->id(), "time");
  _lineWidthsId = glGetUniformLocation(_shader->id(), "lineWidths");
  _amplitudesId = glGetUniformLocation(_shader->id(), "amplitudes");

  _heightMap = std::make_shared<HeightMap>(1);
}

void SoundwaveEffect::drawFrame()
{

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _shader->use();

  float lineWidths[] = {0.05, 0.01, 0.01, 0.01};
  float amplitudes[] = {0.5, 0.4, 0.3, 0.2};

  glUniform1f(_timeId, App::getTime());
  glUniform1fv(_lineWidthsId, 4, lineWidths);
  glUniform1fv(_amplitudesId, 4, amplitudes);

  //draw grid usng shder
  _heightMap->draw(_shader->getPosAttr());

  glDisable(GL_BLEND);
}