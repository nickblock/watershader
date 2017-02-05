//
// Created by nick on 05/02/17.
//

#ifndef WATERSHADER_TEXTURE_H
#define WATERSHADER_TEXTURE_H

#include <GLES2/gl2.h>
#include <vector>

struct ImageData
{
    std::vector<signed char> data;
    int width, height;
};

using ImageDataList = std::vector<ImageData>;

class Texture
{
public:
    Texture(const char* filename);

    void bind();

protected:
    GLuint _id;
};

class CubeMap
{
public:
    CubeMap(const ImageDataList & imageDataList);

    void bind();

protected:
    GLuint _id;
};
#endif //WATERSHADER_TEXTURE_H
