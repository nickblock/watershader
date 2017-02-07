  //
  // Created by nick on 04/02/17.
  //
#include "app.h"
#include "texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#include <cstdlib>
#include <cmath>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

void CHECKGL_ERROR()
{
  GLenum err = glGetError();
  if(err != GL_NO_ERROR) {
    __android_log_print(ANDROID_LOG_INFO, "glError %d %s:%d ", __FILE__, __LINE__);
    std::exit(1);
  }
}

App* App::theApp = nullptr;

void App::loadImage(signed char* data, int dataSize, int width, int height)
{
  ImageData imageData;

  imageData.data.insert(imageData.data.begin(), data, data + dataSize);
  imageData.width = width;
  imageData.height = height;

  _imageData.push_back(imageData);
}

void App::init()
{
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  
  _waterShader = std::make_shared<WaterShader>();

  ImageData debugImage;
  debugImage.width = 4;
  debugImage.height = 4;
  debugImage.data = {4*4*4};
  memset(debugImage.data.data(), 255, debugImage.data.size());

  _cubeMap = std::make_shared<CubeMap>(_imageData);
  _texture = std::make_shared<Texture>(debugImage);

  _heightMap = std::make_shared<HeightMap>(10, 10);

  _eyeDist = 10.f;
  _eyePos = glm::vec3(0, 0, _eyeDist);

}

void App::setScreen(int width, int height)
{
  _width = width;
  _height = height;

  glViewport(0, 0, width, height);
}
void App::drawFrame()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _waterShader->use();

  glActiveTexture(0);
  _texture->bind();


  glm::mat4 view = glm::lookAt(_eyePos, _eyePos + glm::vec3(0, 0, -_eyeDist), glm::vec3(0, 1, 0));

  glm::mat4 proj = glm::perspectiveFov(M_PI/2.0, (double)_width, (double)_height, 0.5, 1000.0);

  glm::mat4 MVP = proj * view;

  _waterShader->setUniforms(MVP, _eyePos, 0.f, 1.f);

  _heightMap->draw(_waterShader->getPosAttr());

}

  void App::touchMove(float x, float y)
  {
    _eyePos += glm::vec3(x, y, 0);
  }
