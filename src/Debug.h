#pragma once
#include <iostream>
#include <sstream>
#include <GL/glew.h>
#include <string>

#define ASSERT(x) if (!(x)) __builtin_trap()
#define GLCall(x) GlClearError();\
  x;\
  ASSERT(GlLogCall(#x, __FILE__,__LINE__))

inline std::string convertHex(int decimal)
{
  std::stringstream ss;
  ss<< std::hex << decimal;
  std::string res ( ss.str() );

  return res;
}

inline void GlClearError()
{
  while (glGetError() != GL_NO_ERROR);
}

inline bool GlLogCall(const char* function, const char* file, const int line)
{
  while(GLenum error = glGetError())
  {
    std::cout << "[Opengl error] (" << convertHex(error) << ")"
      << " in " << function << ", line: " << line << ", file: " << file
      << std::endl;
    return false;
  }
  return true;
}
