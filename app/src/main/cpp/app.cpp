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

  _cubeMap = std::make_shared<CubeMap>(_imageData);

  _heightMap = std::make_shared<HeightMap>(20, 20);
}

void App::setScreen(int width, int height)
{
  _width = width;
  _height = height;

  glViewport(0, 0, width, height);
}
void App::drawFrame()
{
  glClear(GL_COLOR_BUFFER_BIT);

  _waterShader->use();

  glActiveTexture(0);
  _cubeMap->bind();


  glm::vec3 eyePos = glm::vec3(0, 10, 0);
  glm::mat4 view;
  view = glm::lookAt(eyePos, glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));

  glm::mat4 proj = glm::perspective(M_PI/4.0, _height/(double)_width, 0.5, 100.0);

  glm::mat4 MVP = view * proj;

  _waterShader->setUniforms(MVP, eyePos, 0.f, 1.f);

  _heightMap->draw(_waterShader->getPosAttr());

}
void on_surface_created()
{

}