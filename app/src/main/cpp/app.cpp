  //
  // Created by nick on 04/02/17.
  //
#include "app.h"
#include "texture.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <android/log.h>
#include <cstdlib>
#include <cmath>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>

void CHECKGL_ERROR()
{
  GLenum err = glGetError();
  if(err != GL_NO_ERROR) {
    __android_log_print(ANDROID_LOG_INFO, "glError %d %s:%d ", __FILE__, __LINE__);
    std::exit(1);
  }
}

App* App::theApp = nullptr;

  std::vector<float> debugVerts = {
          -0.5,  -0.5, 0.0,
          -0.5,   0.5, 0.0,
          0.5,    0.5, 0.0,
          0.5,   -0.5, 0.0
  };
  std::vector<int> debugIndices = {
    0, 1, 2, 0, 2, 3
  };

  GLuint dVbo, dIbo;

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
  glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
  
  _waterShader = std::make_shared<WaterShader>();

  _cubeMap = std::make_shared<CubeMap>(_imageData);

  _heightMap = std::make_shared<HeightMap>(2, 2);

  _eyePos = glm::vec3(0, 0, 10);

  glGenBuffers(1, &dVbo);
  glBindBuffer(GL_ARRAY_BUFFER, dVbo);
  glBufferData(GL_ARRAY_BUFFER,
               debugVerts.size() * sizeof(float),
               (GLfloat*) debugVerts.data(),
               GL_STATIC_DRAW);

  glGenBuffers(1, &dIbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dIbo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               debugIndices.size() * sizeof(int),
               (GLuint*) debugIndices.data(),
               GL_STATIC_DRAW);
}

void App::setScreen(int width, int height)
{
  _width = width;
  _height = height;

  glViewport(0, 0, width, height);
}
void App::drawFrame()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  _waterShader->use();

  glActiveTexture(0);
  _cubeMap->bind();


  glm::mat4 view = glm::lookAt(_eyePos, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

  glm::mat4 proj = glm::perspectiveFov(M_PI/2.0, (double)_width, (double)_height, 0.5, 1000.0);

  glm::mat4 MVP = proj * view;

  _waterShader->setUniforms(MVP, _eyePos, 0.f, 1.f);

  glBindBuffer(GL_ARRAY_BUFFER, dVbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, dIbo);

  GLuint posAttribute = _waterShader->getPosAttr();
  glEnableVertexAttribArray(posAttribute);
  glVertexAttribPointer(posAttribute,3,GL_FLOAT,GL_FALSE,0,0);

  glDrawElements(
    GL_TRIANGLES,
    debugIndices.size(), 
    GL_UNSIGNED_INT, 
    (void*)0
  );


  //_heightMap->draw(_waterShader->getPosAttr());

}

  void App::touchMove(float x, float y)
  {
    _eyePos += glm::vec3(x, y, 0);
  }
