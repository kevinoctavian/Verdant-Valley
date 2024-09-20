#pragma once

#include "glad/gl.h"

namespace VV::Renderer {
class ElementBuffer {
private:
  GLuint _EBO;
  GLuint _count;

public:
  ElementBuffer(GLuint *indices, GLuint count);
  ~ElementBuffer();

  void Bind();
  void UnBind();

  GLuint GetCount();
};
} // namespace VV::Renderer
