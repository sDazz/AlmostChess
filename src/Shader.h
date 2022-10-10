#pragma once
#include "pch.h"
#include "glm/glm.hpp"
#include "Debug.h"


//Shader sources
struct ShaderProgramSource
{
  std::string VertexSource;
  std::string FragmentSource;
};


class Shader
{
  private:
    unsigned int m_RendererID;
    std::string m_Filepath;
    std::unordered_map<std::string, int> m_UniformLocationCache;


  public:
    Shader(const std::string& filepath);
    ~Shader(){}

    void bind() const;
    void Unbind();

    //SetUniforms
    void SetUniform1i( const std::string& name, int value);
    void SetUniform1f( const std::string& name, float value);
    void SetUniform4f( const std::string& name, float f1,float f2, float f3, float f4);


    void SetUniformVec4( const std::string& name, const glm::vec4& color);
    void SetUniformMat4f( const std::string & name, const glm::mat4& mat);


    int GetUniformLocation(const std::string& name);


    unsigned int getProgram() const{ return m_RendererID;}


  private:
    unsigned int CompileShader(const unsigned int type,
                        const std::string& name);

    unsigned int CreateShader(const std::string& vertexShader,
                      const std::string& fragmentShader);

    unsigned int CheckError(const unsigned int& id, const unsigned int& type,
                  const std::string& source);

    ShaderProgramSource ParseShader(const std::string& filepath);
};

