//
// Created by nick on 18/02/17.
//

#include "soundwave.h"
#include "app.h"

SoundwaveEffect::SoundwaveEffect()
{

  _shader = std::make_shared<SoundwaveShader>();
  _heightMap = std::make_shared<HeightMap>(1);
}

void SoundwaveEffect::drawFrame()
{

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  _shader->use();
  _shader->setUniform(App::getTime());

  //draw grid usng shder
  _heightMap->draw(_shader->getPosAttr());

  glDisable(GL_BLEND);
}