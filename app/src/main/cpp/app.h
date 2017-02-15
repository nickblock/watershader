//
// Created by nick on 04/02/17.
//

#ifndef WATERSHADER_MAIN_H
#define WATERSHADER_MAIN_H

#include "effect.h"
#include "watershader.h"
#include "texture.h"

#include <GLES2/gl2.h>
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

    void loadImage(signed char* data, int dataSize, int width, int height);

    void setScreen(int width, int height);

    void drawFrame();

    void touchMove(float x, float y);

protected:

    ImageDataList  _imageData;
    static App* theApp;

    int _width, _height;

    std::shared_ptr<Effect> _theEffect;
};

void CHECKGL_ERROR();


#endif //WATERSHADER_MAIN_H
