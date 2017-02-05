#include "heightmap.h"


#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>

HeightMap::HeightMap(int rows, int cols)
{
  std::vector<glm::vec3> verts((rows+1) * (cols+1));
  std::vector<int> indices(rows * cols * 6);

  int index = 0;
  for(int y = 0; y<=rows; y++) {
    for(int x=0; x<=cols; x++) {

      int vertIndex = x + y*cols;
      verts[vertIndex] = glm::vec3(x, 0, y);

      if(x != cols && y != rows) {
        indices[index + 0] = vertIndex;
        indices[index + 1] = vertIndex+1;
        indices[index + 2] = vertIndex+cols;
        indices[index + 3] = vertIndex+cols;
        indices[index + 4] = vertIndex+1;
        indices[index + 5] = vertIndex+cols+1;

        index += 6;
      }
    }
  }
  _numIndices = indices.size();

  glGenBuffers(1, &_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glBufferData(GL_ARRAY_BUFFER, 
               verts.size() * sizeof(glm::vec3), 
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
  glVertexAttribPointer(posAttribute,3,GL_FLOAT,GL_FALSE,3,0);

  glDrawElements(
    GL_TRIANGLES, 
    _numIndices, 
    GL_UNSIGNED_INT, 
    (void*)0
  );
}