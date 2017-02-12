//
// Created by nick on 05/02/17.
//

#ifndef WATERSHADER_TEXTURE_H
#define WATERSHADER_TEXTURE_H

#include <GLES2/gl2.h>
#include <vector>

struct ImageData
{
    std::vector<unsigned char> data;
    int width, height;
};


using ImageDataList = std::vector<ImageData>;

class Texture
{
public:
    Texture(const ImageData& imageData);
    virtual ~Texture();

    void bind();

protected:
    GLuint _id;
};

class CubeMap
{
public:
    CubeMap(const ImageDataList & imageDataList);
    virtual ~CubeMap();
    
    void bind();

protected:
    GLuint _id;
};
#endif //WATERSHADER_TEXTURE_H
