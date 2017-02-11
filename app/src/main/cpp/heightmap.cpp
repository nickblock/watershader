#include "heightmap.h"


#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>

HeightMap::HeightMap(int rows, int cols)
{
  std::vector<float> verts((rows+1) * (cols+1) *3);
  std::vector<int> indices(rows * cols * 6);

  float scale = 10.0f;

  float startX = -cols/2.f;
  float startY = -rows/2.f;

  startX *= scale;
  startY *= scale;

  int index = 0;
  for(int y=0; y<=rows; y++) {
    for(int x=0; x<=cols; x++) {

      int vertIndex = (x + y*(cols+1)) * 3;
      verts[vertIndex + 0] = startX + (x * scale);
      verts[vertIndex + 1] = startY + (y * scale);
      verts[vertIndex + 2] = 0;

      if(x != cols && y != rows) {
        vertIndex /= 3;
        indices[index + 0] = vertIndex;
        indices[index + 1] = vertIndex+1;
        indices[index + 2] = vertIndex+cols+1;
        indices[index + 3] = vertIndex+cols+1;
        indices[index + 4] = vertIndex+1;
        indices[index + 5] = vertIndex+cols+2;

        index += 6;
      }
    }
  }
  _numIndices = indices.size();

  glGenBuffers(1, &_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, 
               verts.size() * sizeof(float),
               (GLfloat*) verts.data(),
               GL_STATIC_DRAW);

  glGenBuffers(1, &_ibo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER,
               indices.size() * sizeof(int),
               (GLuint*) indices.data(),
               GL_STATIC_DRAW);

}

void HeightMap::draw(GLuint posAttribute)
{
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);


  glEnableVertexAttribArray(posAttribute);
  glVertexAttribPointer(posAttribute,3,GL_FLOAT,GL_FALSE,0,0);

  glDrawElements(
    GL_TRIANGLES,
    _numIndices, 
    GL_UNSIGNED_INT, 
    (void*)0
  );
}