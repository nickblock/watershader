//
// Created by nick on 05/02/17.
//

#include "watershader.h"
#include "app.h"

#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>

#include <cmath>
#include <string.h>
#include <android/log.h>


const char* waterFrag = {
  "varying vec3 position;\n"
  "varying vec3 worldNormal;\n"
  "uniform vec3 eyePos;\n"
  "uniform samplerCube tex;\n"
  "\n"
  "void main() {\n"
  " vec3 eye = normalize(eyePos - position);\n"
  " vec3 r = reflect(eye, worldNormal);\n"
  " vec4 color = textureCube(tex, r);\n"
  " color.a = 1.0;\n"
  " gl_FragColor = color;\n"
  "}\n"

};

const char* waterVertex = { 
  "attribute vec3 in_position;\n"
  "const float pi = 3.14159;\n"
  "uniform mat4 MVPMatrix;\n"
  "uniform float waterHeight;\n"
  "uniform float time;\n"
  "uniform float in_amp;\n"
  "uniform int numWaves;\n"
  "uniform float amplitude[8];\n"
  "uniform float wavelength[8];\n"
  "uniform float speed[8];\n"
  "uniform vec2 direction[8];\n"
  "varying vec3 position;\n"
  "varying vec3 worldNormal;\n"
  "\n"
  "float wave(int i, float x, float y) {\n"
  " float frequency = 2.0*pi/wavelength[i];\n"
  " float phase = speed[i] * frequency;\n"
  " float theta = dot(direction[i], vec2(x, y));\n"
  " return amplitude[i] * sin(theta * frequency + time * phase);\n"
  "}\n"
  "\n"
  "float waveHeight(float x, float y) {\n"
  " float height = 0.0;\n"
  " for (int i = 0; i < numWaves; ++i)\n"
  " height += wave(i, x, y);\n"
  " return height;\n"
  "}\n"
  "\n"
  "float dWavedx(int i, float x, float y) {\n"
  " float frequency = 2.0*pi/wavelength[i];\n"
  " float phase = speed[i] * frequency;\n"
  " float theta = dot(direction[i], vec2(x, y));\n"
  " float A = amplitude[i] * in_amp * direction[i].x * frequency;\n"
  " return A * cos(theta * frequency + time * phase);\n"
  "}\n"
  "\n"
  "float dWavedy(int i, float x, float y) {\n"
  " float frequency = 2.0*pi/wavelength[i];\n"
  " float phase = speed[i] * frequency;\n"
  " float theta = dot(direction[i], vec2(x, y));\n"
  " float A = amplitude[i] * in_amp * direction[i].y * frequency;\n"
  " return A * cos(theta * frequency + time * phase);\n"
  "}\n"
  "\n"
  "vec3 waveNormal(float x, float y) {\n"
  " float dx = 0.0;\n"
  " float dy = 0.0;\n"
  " for (int i = 0; i < numWaves; ++i) {\n"
  "   dx += dWavedx(i, x, y);\n"
  "   dy += dWavedy(i, x, y);\n"
  " }\n"
  " vec3 n = vec3(-dx, -dy, 1.0);\n"
  " return normalize(n);\n"
  "}\n"
  "\n"
  "void main() {\n"
  " vec4 pos = vec4(in_position, 1.0);\n"
  " pos.z = waterHeight + waveHeight(pos.x, pos.y);\n"
  " position = pos.xyz / pos.w;\n"
  " worldNormal = waveNormal(pos.x, pos.y);\n"
  " gl_Position = MVPMatrix * pos;\n"
  "}\n"
};

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

void compileStatus(GLuint id)
{
  GLint status;
  glGetShaderiv(id, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    GLint logLength;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
    GLchar *buffer = new GLchar[logLength];
    glGetShaderInfoLog(id, logLength, &logLength, buffer);
    __android_log_print(ANDROID_LOG_INFO, "%s", buffer);
    delete [] buffer;
    std::exit(1);
  }
}
WaterShader::WaterShader() {

  _programId = glCreateProgram();

  GLuint vertexId = glCreateShader(GL_VERTEX_SHADER);
  CHECKGL_ERROR();

  int len = strlen(waterVertex);
  glShaderSource(vertexId, 1, &waterVertex, &len);
  CHECKGL_ERROR();

  glCompileShader(vertexId);
  compileStatus(vertexId);
  CHECKGL_ERROR();
  glAttachShader(_programId, vertexId);

  GLuint fragId = glCreateShader(GL_FRAGMENT_SHADER);
  CHECKGL_ERROR();

  len = strlen(waterFrag);
  glShaderSource(fragId, 1, &waterFrag, &len);
  CHECKGL_ERROR();

  glCompileShader(fragId);
  compileStatus(fragId);
  CHECKGL_ERROR();
  glAttachShader(_programId, fragId);

  glLinkProgram(_programId);
  CHECKGL_ERROR();

  glUseProgram(_programId);
  CHECKGL_ERROR();

  _posAttribute = glGetAttribLocation(_programId,"in_position");
  _MVPId = glGetUniformLocation(_programId, "MVPMatrix");
  _timeId = glGetUniformLocation(_programId, "time");
  _ampId = glGetUniformLocation(_programId, "in_amp");
  _eyePosId = glGetUniformLocation(_programId, "eyePos");

  GLuint waterHeightId = glGetUniformLocation(_programId, "waterHeight");
  glUniform1f(waterHeightId, 1.f);
  CHECKGL_ERROR();
  GLuint numWavesId = glGetUniformLocation(_programId, "numWaves");
  glUniform1i(numWavesId, 4);
  CHECKGL_ERROR();
  GLuint envMapId = glGetUniformLocation(_programId, "tex");    
  glUniform1i(envMapId, 0);
  CHECKGL_ERROR();

  for (int i = 0; i < 4; ++i) {
    float amplitude = 0.5f / (i + 1);
    {
      std::stringstream ss;
      ss << "amplitude[" << i << "]";
      GLuint locId = glGetUniformLocation(_programId, ss.str().c_str());
      if(locId >= 0) {
        glUniform1f(locId, amplitude);
      }

      CHECKGL_ERROR();
    }

    float wavelength = 8 * M_PI / (i + 1);
    {
      std::stringstream ss;
      ss << "wavelength[" << i << "]";
      GLuint locId = glGetUniformLocation(_programId, ss.str().c_str());
      if(locId >= 0) {
        glUniform1f(locId, wavelength);
      }

      CHECKGL_ERROR();
    }

    float speed = 1.0f + 2*i;
    {
      std::stringstream ss;
      ss << "speed[" << i << "]";
      GLuint locId = glGetUniformLocation(_programId, ss.str().c_str());
      if(locId >= 0) {
        glUniform1f(locId, speed);
      }

      CHECKGL_ERROR();
    }

    float angle = -M_PI/3 + i * (M_PI/12);
    {
      std::stringstream ss;
      ss << "direction[" << i << "]";
      GLuint locId = glGetUniformLocation(_programId, ss.str().c_str());
      if(locId >= 0) {
        glUniform2f(locId, cos(angle), sin(angle));
      }

      CHECKGL_ERROR();
    }
  }
}

void WaterShader::use()
{
  glUseProgram(_programId);
}

void WaterShader::setUniforms(glm::mat4& mvp, glm::vec3& eyePos, float time, float amplitude)
{
  glUniformMatrix4fv(_MVPId, 1, GL_FALSE, &mvp[0][0]);
  glUniform3f(_eyePosId, eyePos.x, eyePos.y, eyePos.z);
  glUniform1f(_ampId, amplitude);
  glUniform1f(_timeId, time);
}

GLuint WaterShader::getPosAttr()
{
  return _posAttribute;
}