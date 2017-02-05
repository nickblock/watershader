  //
  // Created by nick on 04/02/17.
  //
#include "main.h"
#include "texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

App* App::theApp = nullptr;


  void App::loadImage(signed char* data, int dataSize, int width, int height)
  {
      ImageData imageData;

      imageData.data.insert(imageData.data.begin(), data, data + dataSize);
      imageData.width = width;
      imageData.height = height;

      _imageData.push_back(imageData);
  }

  void App::init()
  {

  }


void on_surface_created()
{
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);

}
void on_surface_changed(int width, int height)
{

}

void on_draw_frame()
{
    glClear(GL_COLOR_BUFFER_BIT);

}