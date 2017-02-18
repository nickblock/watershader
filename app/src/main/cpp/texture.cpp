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

  assert(imageDataList.size() >= 6);

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

const char* textureVertex = {
  "attribute vec3 in_position;\n"
  "attribute vec2 in_uv;\n"
  "varying vec2 uv;\n"
  "void main() {\n"
  "uv = in_uv;\n"
  "gl_Position = vec4(in_position, 1.0);\n"
  "}\n"
};

const char* textureFrag = {
  "uniform sampler2D tex;\n"
  "varying vec2 uv;\n"
  "void main() {\n"
  " gl_FragColor = texture2D(tex, uv);\n"
  "}\n"
};


TextureEffect::TextureEffect(const ImageData& imageData, float posX, float posY, float endX, float endY)
{
  _texture = std::make_shared<Texture>(imageData);

  _shader = std::make_shared<Shader>();
  _shader->compileProgram(textureVertex, textureFrag);

  _posAttr = glGetAttribLocation(_shader->id(),"in_position");
  _uvAttr = glGetAttribLocation(_shader->id(),"in_uv");
  
  _uvs.push_back(glm::vec2(0.0f, 0.0f));
  _uvs.push_back(glm::vec2(0.0f, 1.0f));
  _uvs.push_back(glm::vec2(1.0f, 1.0f));
  _uvs.push_back(glm::vec2(1.0f, 0.0f));
  
  _pos.push_back(glm::vec3(posX, posY, 0.0));
  _pos.push_back(glm::vec3(posX, endY, 0.0));
  _pos.push_back(glm::vec3(endX, endY, 0.0));
  _pos.push_back(glm::vec3(endX, posY, 0.0));

  _indices.push_back(0);
  _indices.push_back(1);
  _indices.push_back(2);
  _indices.push_back(0);
  _indices.push_back(2);
  _indices.push_back(3);
}

void TextureEffect::drawFrame()
{
  _shader->use();

  glActiveTexture(0);
  _texture->bind();


  glEnableVertexAttribArray(_posAttr);
  glVertexAttribPointer(_posAttr,3,GL_FLOAT,GL_FALSE,0,_pos.data());

  glEnableVertexAttribArray(_uvAttr);
  glVertexAttribPointer(_uvAttr,2,GL_FLOAT,GL_FALSE,0,_uvs.data());


  glDrawElements(
    GL_TRIANGLES,
    6, 
    GL_UNSIGNED_INT, 
    (void*)_indices.data()
  );
}