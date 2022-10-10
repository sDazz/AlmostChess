#include "VertexArray.h"
#include "pch.h"


VertexArray::VertexArray()
{
  GLCall(glGenVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
  GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(const VertexBuffer& vb , const VertexBufferLayout& layout)
{

  Bind();
  vb.Bind();
  const auto elements = layout.GetElements();

  uintptr_t offset = 0;
  for(unsigned int i = 0; i < elements.size(); i++)
  {

    const auto& element = elements[i];
    GLCall(glEnableVertexAttribArray(i));
    GLCall(glVertexAttribPointer(i,
                                 element.count,
                                 element.type,
                                 element.normalized,
                                 layout.GetStride(),
                                 (const void*) offset));



    offset += element.count * VertexBufferElement::getSizeOfType(element.type);

  }
}

void VertexArray::Bind() const
{
  GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
  GLCall(glBindVertexArray(0));
}

