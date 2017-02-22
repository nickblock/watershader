#include "framebuffer.h"
#include "app.h"


FrameBuffer::FrameBuffer(int width, int height) : 
  _inited(false),
  _width(width),
  _height(height)
{
  resize(width, height);
}
void FrameBuffer::resize(int width, int height)
{

  if(_inited) {
    if(_width == width && _height == height) {
      return;
    }
    destroy();
  }

  glGenFramebuffers(1, &_fboId);
  glBindFramebuffer(GL_FRAMEBUFFER, _fboId);

  glGenTextures(1, &_colorId);
  glBindTexture(GL_TEXTURE_2D, _colorId);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,  width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  std::vector<GLbyte> bytes(width*height*4, 0);
  glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,bytes.data());
  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _colorId, 0);

  glGenRenderbuffers(1, &_depthId);
  glBindRenderbuffer(GL_RENDERBUFFER, _depthId);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT16, width, height);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, _depthId);

  GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if(status != GL_FRAMEBUFFER_COMPLETE) {
      assert(0);
      destroy();
  }
  else {
    _inited = true;
  }
}

void FrameBuffer::destroy()
{
  glDeleteFramebuffers(1, &_fboId);
  glDeleteTextures(1, &_colorId);
  glDeleteRenderbuffers(1, &_depthId);

  _inited = false;
}

void FrameBuffer::bindFBO()
{
  glBindFramebuffer(GL_FRAMEBUFFER, _fboId);
}

void FrameBuffer::bindTex()
{
  glBindTexture(GL_TEXTURE_2D, _colorId);
}