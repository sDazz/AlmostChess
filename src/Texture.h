#pragma once
#include "pch.h"
#include "stb_image/stb_image.h"


class Texture
{
  private:
    unsigned int m_RendererID;
    std::string m_filepath = "";
    int m_Width,m_Height,m_BPP;
    unsigned char* m_LocalBuffer;

  public:

    Texture(const std::string& filepath);
    Texture()
      :m_RendererID(0),m_Width(0),m_Height(0), m_BPP(0)
    {}
    ~Texture();

    void make(const std::string& filepath);
    void bind(unsigned int count = 0) const;
    unsigned int getTextureID() const { return m_RendererID; }
    void Unbind() const;
};

