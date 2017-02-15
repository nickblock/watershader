//
// Created by nick on 15/02/17.
//

#ifndef WATERSHADER_EFFECT_H
#define WATERSHADER_EFFECT_H


class Effect {

public:

  virtual void setScreen(int width, int height) = 0;

  virtual void drawFrame() = 0;

  virtual void touchMove(float x, float y) = 0;

};


#endif //WATERSHADER_EFFECT_H
