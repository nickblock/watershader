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

protected:
  GLuint _programId;
};


#endif //WATERSHADER_SHADER_H
