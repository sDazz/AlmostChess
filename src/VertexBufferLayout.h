#pragma once
#include <GL/glew.h>
#include "Debug.h"
#include <vector>

struct VertexBufferElement
{
  unsigned int type;
  unsigned int count;
  unsigned char normalized;

  static unsigned int getSizeOfType(unsigned int type)
  {
    switch(type)
    {
      case GL_FLOAT:            return 4;
      case GL_UNSIGNED_INT:     return 4;
      case GL_UNSIGNED_BYTE:    return 4;
    }
    ASSERT(type);
    return 0;
  }
};



class VertexBufferLayout
{
  private:
    unsigned int m_RendererID;
    unsigned int m_Stride;

    std::vector<VertexBufferElement> m_Elements;

  public:
    VertexBufferLayout()
      :m_Stride(0){}
    ~VertexBufferLayout()
    {
    }

    inline std::vector<VertexBufferElement> GetElements() const { return m_Elements; }
    inline unsigned int GetStride() const {return m_Stride; }

    //Definitions right below
    template<typename T>
    void Push(unsigned int count) ;

};
template<>
inline void VertexBufferLayout::Push<float>(unsigned int count)
{
  m_Elements.push_back( {GL_FLOAT, count, GL_FALSE});
  m_Stride += count * VertexBufferElement::getSizeOfType(GL_FLOAT);
}

template<>
inline void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
  m_Elements.push_back( {GL_UNSIGNED_INT, count, GL_TRUE});
  m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_INT);
}
template<>
inline void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
  m_Elements.push_back( {GL_UNSIGNED_BYTE, count, GL_TRUE});
  m_Stride += count * VertexBufferElement::getSizeOfType(GL_UNSIGNED_BYTE);
}
/*
   //this still an incognito
  GLCall(GLint posAttrib = glGetAttribLocation(shaderProgram, "position"));
*/
