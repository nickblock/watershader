//
// Created by nick on 15/02/17.
//

#include "shader.h"
#include "app.h"

#include <cstdlib>
#include <string.h>

void compileStatus(GLuint id)
{
  GLint status;
  glGetShaderiv(id, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE) {
    GLint logLength;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
    GLchar *buffer = new GLchar[logLength];
    glGetShaderInfoLog(id, logLength, &logLength, buffer);
    LOG("%s", buffer);
    delete [] buffer;
    std::exit(1);
  }
}

GLuint compileShader(const char* source, GLenum shaderType) 
{
  GLuint shaderId = glCreateShader(shaderType);
  CHECKGL_ERROR();

  int len = strlen(source);
  glShaderSource(shaderId, 1, &source, &len);
  CHECKGL_ERROR();

  glCompileShader(shaderId);
  compileStatus(shaderId);
  CHECKGL_ERROR();

  return shaderId;
}


void Shader::compileProgram(const char* vertexSource, const char* fragSource)
{
  _programId = glCreateProgram();

  GLuint vertexId = compileShader(vertexSource, GL_VERTEX_SHADER);
  glAttachShader(_programId, vertexId);

  GLuint fragId = compileShader(fragSource, GL_FRAGMENT_SHADER);
  glAttachShader(_programId, fragId);

  glLinkProgram(_programId);
  CHECKGL_ERROR();

  glUseProgram(_programId);
  CHECKGL_ERROR();

  //common uniforms for all our shaders
  _posAttrId = glGetAttribLocation(_programId,"in_position");
}

Shader::~Shader()
{
  glDeleteShader(_programId);
}

void Shader::use()
{
  glUseProgram(_programId);
}
GLuint Shader::id()
{
  return _programId;
}

GLuint Shader::getPosAttr()
{
  return _posAttrId;
}