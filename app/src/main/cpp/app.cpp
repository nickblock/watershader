  //
  // Created by nick on 04/02/17.
  //
#include "app.h"
#include "watereffect.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#include <cstdlib>

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

  _theEffect = std::shared_ptr<Effect>(new WaterEffect(_imageData));  
}

void App::setScreen(int width, int height)
{
  _width = width;
  _height = height;

  glViewport(0, 0, width, height);

  _theEffect->setScreen(width, height);
}
void App::drawFrame()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _theEffect->drawFrame();
}

void App::touchMove(float x, float y)
{
  _theEffect->touchMove(x, y);
}
