  //
  // Created by nick on 04/02/17.
  //
#include "app.h"
#include "watereffect.h"
#include "hearteffect.h"
#include "soundwave.h"
#include "smokeeffect.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>

#include <time.h>
#define NS_IN_SEC 1000000000

#ifdef WIN32
#include "time_win.h"
#endif
const int Android_Action_Move = 2;
const int Android_Action_Down = 0;
const int Android_Action_Up = 1;

void CHECKGL_ERROR()
{
  GLenum err = glGetError();
  if(err != GL_NO_ERROR) {
    LOG("glError %s:%d ", __FILE__, __LINE__);
    assert(0);
  }
}

App* App::theApp = nullptr;

void App::loadImage(const signed char* data, int dataSize, int width, int height)
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

  _effectList.push_back(std::shared_ptr<Effect>(new HeartEffect()));

  _effectList.push_back(std::shared_ptr<Effect>(new SoundwaveEffect()));

  _effectList.push_back(std::shared_ptr<Effect>(new WaterEffect(_imageData)));

  _effectList.push_back(std::shared_ptr<Effect>(new SmokeEffect(0, 0)));

  _bgShader = std::make_shared<BgShader>();
  _quad = std::make_shared<HeightMap>(1);

  glDisable(GL_DEPTH_TEST);

  _currentEffect = 3;

  _gradients.push_back(Gradient(
    glm::vec3(102/255.f, 200/255.f, 209/255.f), 
    glm::vec3(158/255.f, 160/255.f, 240/255.f)
  )); 

  _gradients.push_back(Gradient(
    glm::vec3(111/255.f, 210/255.f, 210/255.f),
    glm::vec3(255/255.f, 255/255.f, 115/255.f)
  )); 

  _gradients.push_back(Gradient(
    glm::vec3(255/255.f, 117/255.f, 101/255.f),
    glm::vec3(156/255.f, 159/255.f, 240/255.f)
  )); 
}

void App::setScreen(int width, int height)
{
  _width = width;
  _height = height;

  glViewport(0, 0, width, height);

  _effectList[_currentEffect]->setScreen(width, height);
}
void App::drawFrame()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Gradient& gradient = _gradients[0];

  _bgShader->use();
  _bgShader->setUniform(gradient.first, gradient.second);
  _quad->draw(_bgShader->getPosAttr());

  _effectList[_currentEffect]->drawFrame();
}

void App::touchMove(float x, float y)
{
  _effectList[_currentEffect]->touchMove(x, y);
}

void App::motionEvent(int type, float eventX, float eventY)
{
  if(Android_Action_Down == type)
  {
      touchX = eventX;
      touchY = eventY;
  }
  else if(Android_Action_Up == type) {

    if(abs(touchX - eventX) < 10 && abs(touchY - eventY) < 10)
    {
      nextEffect();
    } 
  }
  else if(Android_Action_Move == type) {
      
      float moveX = eventX - touchX;
      float moveY = eventY - touchY;

      touchMove(moveX * 0.01, moveY * 0.01);

      touchX = eventX;
      touchY = eventY;
  }

}

void App::nextEffect()
{
  _currentEffect++;
  if(_currentEffect >= _effectList.size()) {
    _currentEffect = 0;
  }

  _effectList[_currentEffect]->setScreen(_width, _height);
}


float App::getTime()
{

#ifndef WIN32
  //get current time in format float seconds using high res timer
  timespec curTime;
  clock_gettime(CLOCK_MONOTONIC, &curTime);

  double time = (double)curTime.tv_sec + (double)curTime.tv_nsec / 1000000000.0;
#else
  timeval curTime;
  clock_gettime(CLOCK_MONOTONIC, &curTime);

  double time = (double)curTime.tv_sec + (double)curTime.tv_usec / 1000000.0;
#endif

  return time;
}
