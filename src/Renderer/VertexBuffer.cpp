#include "Renderer/VertexBuffer.hpp"
#include "Logs/Logs.hpp"

using namespace VV::Renderer;

VertexBuffer::VertexBuffer(unsigned int size) {
  glGenBuffers(1, &_VBO);
  VV_ASSERT(glGetError() == GL_NO_ERROR, "Can't generate Vertex Buffer")

  Bind();

  glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
  VV_ASSERT(glGetError() == GL_NO_ERROR,
            "Can't add data to Vertex Buffer with size {}", size)
}
VertexBuffer::VertexBuffer(float *vertices, unsigned int size) {
  glGenBuffers(1, &_VBO);
  VV_ASSERT(glGetError() == GL_NO_ERROR, "Can't generate Vertex Buffer")

  Bind();

  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  VV_ASSERT(glGetError() == GL_NO_ERROR,
            "Can't add data to Vertex Buffer with size {}", size)
}
VertexBuffer::~VertexBuffer() {
  glDeleteBuffers(1, &_VBO);
  VV_ASSERT(glGetError() == GL_NO_ERROR, "Can't delete vertex buffer, id = {}",
            _VBO)
}

void VertexBuffer::Bind() {
  glBindBuffer(GL_ARRAY_BUFFER, _VBO);
  VV_ASSERT(glGetError() == GL_NO_ERROR, "Can't bind vertex buffer, id = {}",
            _VBO)
}
void VertexBuffer::UnBind() {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  VV_ASSERT(glGetError() == GL_NO_ERROR, "Can't unbind vertex buffer, id = {}",
            _VBO)
}

void VertexBuffer::SetData(float *vertices, unsigned int size) {
  Bind();

  glBufferSubData(GL_ARRAY_BUFFER, 0, size, vertices);
  VV_ASSERT(glGetError() == GL_NO_ERROR,
            "Can't set vertex buffer data, id = {}", _VBO)
}
