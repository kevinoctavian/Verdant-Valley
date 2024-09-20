#pragma once

#include "glad/gl.h"

namespace VV::Renderer {
class VertexBuffer {
private:
  GLuint _VBO;

public:
  VertexBuffer(unsigned int size);
  VertexBuffer(float *verticies, unsigned int size);
  ~VertexBuffer();

  void Bind();
  void UnBind();

  void SetData(float *vertices, unsigned int size);
};
} // namespace VV::Renderer
