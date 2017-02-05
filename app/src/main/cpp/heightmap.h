#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H

#include <GLES2/gl2.h>

class HeightMap {

public:
  HeightMap(int rows, int cols);

  void draw(GLuint posAttribute);
  
protected:
  GLuint _vbo;
  GLuint _ibo;

  int _numIndices;
};

#endif