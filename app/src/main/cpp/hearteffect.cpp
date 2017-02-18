 //
// Created by nick on 15/02/17.
//

#include "hearteffect.h"
#include "app.h"

HeartEffect::HeartEffect()
{
  _shader = std::make_shared<HeartShader>();

  _heightMap = std::make_shared<HeightMap>(1);
}

void HeartEffect::drawFrame()
{
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _shader->use();
  _shader->setUniform(_width, _height, App::getTime());

  //draw grid usng shder
  _heightMap->draw(_shader->getPosAttr());

  glDisable(GL_BLEND);
}

void HeartEffect::touchMove(float x, float y)
{

}
