#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include "gl_include.h"

class HeightMap {

public:
  HeightMap(int dim);
  virtual ~HeightMap();

  void draw(GLuint posAttribute);
  
protected:
  GLuint _vbo;
  GLuint _ibo;

  int _numIndices;
};

#endif