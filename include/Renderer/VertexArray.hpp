#pragma once

#include "glad/gl.h"

namespace VV::Renderer {
class VertexArray {
private:
  GLuint _VAO;

public:
  VertexArray();
  ~VertexArray();

  void Bind();
  void UnBind();
};
} // namespace VV::Renderer
