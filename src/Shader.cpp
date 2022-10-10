#include "Shader.h"


Shader::Shader(const std::string& filepath)
  :m_RendererID(0), m_Filepath(filepath)
{
  ShaderProgramSource source = ParseShader(filepath);
  m_RendererID = CreateShader( source.VertexSource, source.FragmentSource);
//  GLCall(glBindFragDataLocation(m_RendererID, 1, "outColor"));
  //Bind();
}


void Shader::bind() const
{
   GLCall(glUseProgram(m_RendererID));
}
ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
  std::ifstream file(filepath.c_str());

  std::string line;
  std::stringstream ss[2];

  enum ShaderType
  {
    NONE = -1, VERTEX_SHADER = 0, FRAGMENT_SHADER = 1
  };

  int type = ShaderType::NONE;
  while(file.good())
  {
    std::getline(file,line);

    if (line.find("#shader") != std::string::npos)
    {
      if (line.find("vertex") != std::string::npos)
      {
        type = ShaderType::VERTEX_SHADER;
      }
      else if(line.find("fragment") != std::string::npos)
      {
        type = ShaderType::FRAGMENT_SHADER;
      }
    }
    else
    {
      ss[type] << line << "\n";
    }
  }
  if(type==ShaderType::NONE)
    std::cout << "ERROR PARSING SHADER: probably couldn't find '#shader' indicative" << std::endl;

  return{ss[0].str(), ss[1].str()};
}

unsigned int Shader::CreateShader( const std::string& vertexShader,
                            const std::string& fragmentShader)
{
  GLCall(unsigned int shaderProgram = glCreateProgram());
  GLCall(unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader));
  GLCall(unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader));

  GLCall(glAttachShader(shaderProgram, vs));
  GLCall(glAttachShader(shaderProgram, fs));
  glLinkProgram(shaderProgram);
  glValidateProgram(shaderProgram);
  glDeleteShader(vs);
  glDeleteShader(fs);

  return shaderProgram;
};
unsigned int Shader::CompileShader(const unsigned int type,
                            const std::string& source)
{
   unsigned int id = glCreateShader(type);
   const char* src = source.c_str();
   //              = &source[0] and source must be "alive"
   //              'cause this is essencially a pointer
   glShaderSource(id, 1, &src, nullptr);
   glCompileShader(id);
   //some error handling
   CheckError(id, type, src);
   return id;
}

void Shader::SetUniform1i(const std::string& name,int value)
{
  GLCall(glUniform1i(GetUniformLocation(name), value));
}

void Shader::SetUniform1f(const std::string& name, float value)
{
  GLCall(glUniform1f(GetUniformLocation(name), value));
}

void Shader::SetUniform4f(const std::string& name, float v0
                                                 , float v1
                                                 , float v2
                                                 , float v3)
{
  GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

void Shader::SetUniformVec4(const std::string& name, const glm::vec4& color)
{
  SetUniform4f(name,color[0],color[1],color[2],color[3]);
}


void Shader::SetUniformMat4f(const std::string& name, const glm::mat4& mat)
{
  GLCall(glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &mat[0][0]));
}





int Shader::GetUniformLocation(const std::string& name)
{
  if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
    return m_UniformLocationCache[name];

  GLCall(int location = glGetUniformLocation(m_RendererID,name.c_str()));
  if (location == -1)
  {
    std::cout << "WARNING: uniform '" << name << "' Doesn't exist!" << std::endl;
  }
  m_UniformLocationCache[name] = location;

  return location;
}

unsigned int Shader::CheckError(const unsigned int& id,
                                 const unsigned int& type,
                                 const std::string& source)
{
   //some error handling
   int result;
   glGetShaderiv(id, GL_COMPILE_STATUS, &result);
   if (result == GL_FALSE)
   {
     int length ;
     glGetShaderiv(id,GL_INFO_LOG_LENGTH, &length);
     char* message = (char*)alloca(length * sizeof(char));
     glGetShaderInfoLog(id, length, &length, message);
     std::cout << "failed to compile" << " " <<
       (type == GL_VERTEX_SHADER ? "vertex" : "fragment")<< "shader"
       << std::endl;
     std::cout << message << std::endl;
     return 0;
   }
   return 1;
}
