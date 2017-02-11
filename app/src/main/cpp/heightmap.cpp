#include "heightmap.h"


#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>

HeightMap::HeightMap(int dim)
{
  std::vector<glm::vec3> verts((dim+1) * (dim+1));
  std::vector<int> indices(dim * dim * 6);

  float scale = 1.f;//10.f / dim;

  float start = -dim/2.f;

  start *= scale;

  int index = 0;
  for(int y=0; y<=dim; y++) {
    for(int x=0; x<=dim; x++) {

      int vertIndex = (x + y*(dim+1));
      verts[vertIndex].x = start + (x * scale);
      verts[vertIndex].y = start + (y * scale);
      verts[vertIndex].z = 0;

      if(x != dim && y != dim) {
        indices[index + 0] = vertIndex;
        indices[index + 1] = vertIndex+1;
        indices[index + 2] = vertIndex+dim+1;
        indices[index + 3] = vertIndex+dim+1;
        indices[index + 4] = vertIndex+1;
        indices[index + 5] = vertIndex+dim+2;

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
  glVertexAttribPointer(posAttribute,3,GL_FLOAT,GL_FALSE,0,0);

  glDrawElements(
    GL_TRIANGLES,
    _numIndices, 
    GL_UNSIGNED_INT, 
    (void*)0
  );
}