//
// Created by nick on 18/02/17.
//

#ifndef WATERSHADER_SOUNDWAVESHADER_H
#define WATERSHADER_SOUNDWAVESHADER_H

#include "shader.h"

class SoundwaveShader : public Shader{
public:
  
  SoundwaveShader();

  void setUniform(float time);

protected:

  GLuint _timeId;
};


#endif //WATERSHADER_SOUNDWAVESHADER_H
