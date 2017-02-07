//
// Created by nick on 05/02/17.
//
#include "texture.h"
#include "app.h"

Texture::Texture(const char *filename) {

}

CubeMap::CubeMap(const ImageDataList & imageDataList) {

  assert(imageDataList.size() == 6);

  glGenTextures(1, &_id);
  glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_GENERATE_MIPMAP, GL_TRUE);
  for (int i = 0; i < 6; ++i) {

    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                 0,
                 GL_RGB,
                 imageDataList[i].width,
                 imageDataList[i].height,
                 0,
                 GL_RGB,
                 GL_UNSIGNED_BYTE,
                 imageDataList[i].data.data());

    CHECKGL_ERROR();
  }
}
void CubeMap::bind()
{
  glBindTexture(GL_TEXTURE_CUBE_MAP, _id);
}
