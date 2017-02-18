//
// Created by nick on 15/02/17.
//

#ifndef WATERSHADER_SHADER_H
#define WATERSHADER_SHADER_H

#include "gl_include.h"

class Shader {

public:

  virtual ~Shader();

  void compileProgram(const char* vertexSource, const char* fragSource);

  void use();

  GLuint getPosAttr();
  GLuint id();
  
protected:
  GLuint _programId;
  GLuint _posAttrId;

};


#endif //WATERSHADER_SHADER_H
