#include "Renderer/ElementBuffer.hpp"
#include "Logs/Logs.hpp"

using namespace VV::Renderer;

ElementBuffer::ElementBuffer(GLuint *indices, GLuint count) {
  glGenBuffers(1, &_EBO);
  VV_ASSERT(glGetError() == GL_NO_ERROR, "Can't generate Element Buffer")
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count, indices, GL_STATIC_DRAW);
}
ElementBuffer::~ElementBuffer() {
  glDeleteBuffers(1, &_EBO);
  VV_ASSERT(glGetError() == GL_NO_ERROR, "Can't delete Element Buffer")
}

void ElementBuffer::Bind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
  VV_ASSERT(glGetError() == GL_NO_ERROR, "Can't bind Element Buffer")
}
void ElementBuffer::UnBind() {
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  VV_ASSERT(glGetError() == GL_NO_ERROR, "Can't unbind Element Buffer")
}

unsigned int ElementBuffer::GetCount() { return _count; }
