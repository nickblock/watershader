//
// Created by nick on 15/02/17.
//

#include "watereffect.h"
#include "app.h"
#include <cmath>
#include <algorithm>

WaterEffect::WaterEffect(const ImageDataList& imageData)
{
  _waterShader = std::make_shared<WaterShader>();

  //pass raw image data to cubemap 
  _cubeMap = std::make_shared<CubeMap>(imageData);

  _heightMap = std::make_shared<HeightMap>(100);

  _eyeDist = 50.f;
  _eyePos = glm::vec3(0, 0, _eyeDist);
  _mousePos = glm::vec2(0.5);
}

void WaterEffect::drawFrame()
{

  //wave amplitude controlled by mouse Y.
  float waveAmp = _mousePos.y;

  //spin the cubemap around
  glm::mat4 rotateView;
  rotateView = glm::rotate(rotateView, (float)(_mousePos.x * M_PI* 2.f), glm::vec3(0, 1, 0));

  //create view + projection matrix
  glm::mat4 view = glm::lookAt(_eyePos, _eyePos + glm::vec3(0, 0, -_eyeDist), glm::vec3(0, 1, 0));
  glm::mat4 proj = glm::perspectiveFov(M_PI/2.0, (double)_width, (double)_height, 0.5, 1000.0);
  glm::mat4 MVP = proj * view;
  
  _waterShader->use();

  glActiveTexture(0);
  _cubeMap->bind();

  //set shader uniforms
  _waterShader->setUniforms(MVP, _eyePos, (float)App::getTime(), waveAmp, rotateView);

  //draw grid usng shder
  _heightMap->draw(_waterShader->getPosAttr());

}

void WaterEffect::touchMove(float x, float y)
{
    //clamp the y motion to 0-1
    //allow the x motion to cycle around
    _mousePos += glm::vec2(x/10.f, -y/10.f);
    
    if(_mousePos.x > 1.0f)
      _mousePos.x -= 1.0f;
    else if(_mousePos.x < 0.0)
      _mousePos.x += 1.0;

    _mousePos.y = std::max(0.f, std::min(1.f, _mousePos.y));

}
