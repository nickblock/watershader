#include "heightmap.h"

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>

#include <vector>

const float defaultQuad[] = {
  -0.5, -0.5, 0.0,
  -0.5, 0.5, 0.0,
   0.5, 0.5, 0.0,
   0.5, -0.5, 0.0
};

const int defaultQuadIndices[] = {
  0, 1, 2, 0, 2, 3
};

HeightMap::HeightMap(int dim)
{
  //construct a uniform centered grid with triangle indicdes
  std::vector<glm::vec3> verts((dim+1) * (dim+1));
  std::vector<int> indices(dim * dim * 6);

  float start = -dim;


  int index = 0;
  for(int y=0; y<=dim; y++) {
    for(int x=0; x<=dim; x++) {

      int vertIndex = (x + y*(dim+1));
      verts[vertIndex].x = start + (x * 2.f);
      verts[vertIndex].y = start + (y * 2.f);
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

  //load the grid data into the gpu
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
HeightMap::~HeightMap()
{
  glDeleteBuffers(1, &_vbo);
  glDeleteBuffers(1, &_ibo);
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

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
