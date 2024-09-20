#include "Renderer/VertexArray.hpp"

#include "Logs/Logs.hpp"

using namespace VV::Renderer;

VertexArray::VertexArray() {
  glGenVertexArrays(1, &_VAO);
  VV_ASSERT(glGetError() == GL_NO_ERROR, "Can't generate Vertex Array")
}
VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &_VAO);
  VV_ASSERT(glGetError() == GL_NO_ERROR, "Can't delete Vertex Array")
}

void VertexArray::Bind() {
  glBindVertexArray(_VAO);
  VV_ASSERT(glGetError() == GL_NO_ERROR, "Can't bind Vertex Array")
}
void VertexArray::UnBind() {
  glBindVertexArray(0);
  VV_ASSERT(glGetError() == GL_NO_ERROR, "Can't UnBind Vertex Array")
}
