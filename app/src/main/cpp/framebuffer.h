#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include "gl_include.h"

class FrameBuffer
{
public:
  FrameBuffer(int width, int height);

  void resize(int width, int height);

  void bindFBO();
  void bindTex();
  
protected:

  void destroy();

  bool _inited;
  int _width, _height;

  GLuint _fboId;
  GLuint _colorId;
  GLuint _depthId;
};

#endif