#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const void* data, unsigned int count)
  :m_RendererID(0),m_Count(count)
{
  GLCall(glGenBuffers(1, &m_RendererID));
  Bind();
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(GLuint) , data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
  glDeleteBuffers(GL_ELEMENT_ARRAY_BUFFER, &m_RendererID);
}

void IndexBuffer::Bind() const
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID));
}

void IndexBuffer::Unbind() const
{
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0));
}

