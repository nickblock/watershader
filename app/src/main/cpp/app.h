//
// Created by nick on 04/02/17.
//

#ifndef WATERSHADER_MAIN_H
#define WATERSHADER_MAIN_H

#include "watershader.h"
#include "texture.h"
#include "heightmap.h"

#include <GLES2/gl2.h>
#include <vector>
#include <memory>


typedef long long nsec;
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


    std::shared_ptr<WaterShader>    _waterShader;
    std::shared_ptr<CubeMap>        _cubeMap;
    std::shared_ptr<Texture>        _texture;
    std::shared_ptr<HeightMap>      _heightMap;

    ImageDataList  _imageData;
    static App* theApp;

    int _width, _height;

    glm::vec3 _eyePos;
    glm::vec3 _mousePos;
    float     _eyeDist;

    nsec _startTime;
};

void CHECKGL_ERROR();


#endif //WATERSHADER_MAIN_H
