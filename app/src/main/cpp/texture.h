//
// Created by nick on 05/02/17.
//

#ifndef WATERSHADER_TEXTURE_H
#define WATERSHADER_TEXTURE_H

#include "gl_include.h"
#include "shader.h"
#include "effect.h"
#include <vector>

struct ImageData
{
  std::vector<unsigned char> data;
  int width, height;
};


using ImageDataList = std::vector<ImageData>;

class Texture
{
public:
  Texture(const ImageData& imageData);
  virtual ~Texture();

  void bind();

protected:
  GLuint _id;
};

class CubeMap
{
public:
  CubeMap(const ImageDataList & imageDataList);
  virtual ~CubeMap();

  void bind();

protected:
  GLuint _id;
};

class TextureEffect : public Effect 
{
public:
  TextureEffect(const ImageData& image, float posX, float posY, float width, float height);

  virtual void drawFrame();

protected:
  std::shared_ptr<Texture> _texture;
  std::shared_ptr<Shader> _shader;

  float _posX, _posY, _width, _height;

  std::vector<glm::vec3> _pos;
  std::vector<glm::vec2> _uvs;
  std::vector<int>       _indices;

  GLuint _posAttr, _uvAttr;
};
#endif //WATERSHADER_TEXTURE_H
