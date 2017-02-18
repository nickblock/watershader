//
// Created by nick on 04/02/17.
//

#ifndef WATERSHADER_MAIN_H
#define WATERSHADER_MAIN_H

#include "effect.h"
#include "bgshader.h"
#include "texture.h"
#include "heightmap.h"
#include "gl_include.h"

#include <vector>
#include <memory>

//singleton class to handle openges effect
class App
{
public:
    static App* get() {
        if(theApp == 0) {
            theApp = new App();
        }
        return theApp;
    }

    void init();

    void loadImage(const signed char* data, int dataSize, int width, int height);

    void setScreen(int width, int height);

    void drawFrame();

    void motionEvent(int type, float x, float y);

    void touchMove(float x, float y);

    static float getTime();

protected:

    ImageDataList  _imageData;
    static App* theApp;

    int _width, _height;
    float touchX, touchY;

    std::vector<std::shared_ptr<Effect>> _effectList;

    std::shared_ptr<BgShader> _bgShader;
    std::shared_ptr<HeightMap> _quad;

    int _currentEffect;
};

void CHECKGL_ERROR();


#endif //WATERSHADER_MAIN_H
