#shader vertex
#version 330 core

layout (location = 0) in vec2   position;
layout (location = 1) in vec3   color;
layout (location = 2) in vec2   texcoord;
out vec3 Color;
out vec2 Texcoord;

uniform mat4 u_MVP;

void main()
  {
    Color = color;
    Texcoord = texcoord;
    gl_Position = u_MVP * vec4(position, 0.0, 1.0) ;
  }

#shader fragment
#version 330 core

in vec3 Color;
in vec2 Texcoord;

out vec4 outColor;
uniform sampler2D u_Pawn;
void main()
{
  vec4 pawn = texture(u_Pawn,Texcoord);
  outColor = pawn;
}
