//
// Created by nick on 15/02/17.
//

#include "heartshader.h"



const char* simpleVertex = {
  "attribute vec3 in_position;\n"
  "varying vec3 pos;\n"
  "uniform mat4 MVPMatrix;\n"
  "void main() {\n"
  "pos = in_position;\n"
  "gl_Position = MVPMatrix * vec4(in_position, 1.0);\n"
  "}\n"
};

const char* simpleFrag = {
  "uniform samplerCube tex;\n"
  "varying vec3 pos;\n"
  "uniform vec3 eyePos;\n"
  "void main() {\n"
  "vec3 normPos = vec3(0.1 * pos.xy + vec2(0.5, 0.5), 1.0);\n"
  "gl_FragColor = vec4(textureCube(tex, normalize(normPos)).rgb, 1.0);\n"
  "//gl_FragColor = vec4(texture2D(tex, normPos.xy).xyz, 1.0);\n"
  "}\n"
};