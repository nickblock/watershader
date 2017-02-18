//
// Created by nick on 05/02/17.
//
#include "texture.h"
#include "app.h"

GLenum getBits(const ImageData& imageData) {
  int bpp = imageData.data.size() / (imageData.width * imageData.height);

  return bpp == 3 ? GL_RGB : GL_RGBA;
}

void loadImageGL(GLenum type, const ImageData& imageData) {

  glTexImage2D(type,
    0,
    getBits(imageData),
    imageData.width,
    imageData.height,
    0,
    getBits(imageData),
    GL_UNSIGNED_BYTE,
    imageData.data.data());
}

Texture::Texture(const ImageData& imageData) {

  glGenTextures(1, &_id);
  glBindTexture(GL_TEXTURE_2D, _id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  loadImageGL(GL_TEXTURE_2D, imageData);

  CHECKGL_ERROR();
}
Texture::~Texture()
{
  glDeleteTextures(1, &_id);
}
void Texture::bind()
{
  glBindTexture(GL_TEXTURE_2D, _id);
}

CubeMap::CubeMap(const ImageDataList & imageDataList) {

  assert(imageDataList.size() == 6);

  glGenTextures(1, &_id);
  glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE);
  for (int i = 0; i < 6; ++i) {

    loadImageGL(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, imageDataList[i]);

    CHECKGL_ERROR();
  }
  glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

  CHECKGL_ERROR();
}
CubeMap::~CubeMap()
{
  glDeleteTextures(1, &_id);
}
void CubeMap::bind()
{
  glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
}
