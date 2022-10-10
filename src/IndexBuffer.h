#pragma once
#include "pch.h"

class IndexBuffer
{
  private:
    unsigned int m_RendererID;
    unsigned int m_Count;

  public:
    IndexBuffer(const void* data, unsigned int count);
    ~IndexBuffer();

    void Bind() const;
    void Unbind() const;
    unsigned int getCount() const {return m_Count;}
};
