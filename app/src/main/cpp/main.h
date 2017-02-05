//
// Created by nick on 04/02/17.
//

#ifndef WATERSHADER_MAIN_H
#define WATERSHADER_MAIN_H

#include "watershader.h"
#include "texture.h"

#include <GLES2/gl2.h>
#include <vector>
#include <memory>

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

protected:


    std::shared_ptr<WaterShader>    _waterShader;
    std::shared_ptr<CubeMap>        _cubeMap;
    
    ImageDataList  _imageData;
    static App* theApp;
};




void on_surface_created();
void on_surface_changed(int width, int height);
void on_draw_frame();


#endif //WATERSHADER_MAIN_H
