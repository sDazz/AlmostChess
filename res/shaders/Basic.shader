#shader vertex
#version 150 core

in vec2   position;
in vec3   color;
in vec2   texcoord;
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
#version 150 core

in vec3 Color;
in vec2 Texcoord;
out vec4 outColor;
uniform sampler2D texDaz;
uniform sampler2D texGoogle;
uniform vec4 my_color;
void main()
{
  vec4 colDaz = vec4(1.0,0.0,0.0,1.0);
  vec4 colGoogle = vec4(0.0,1.0,0.0,1.0);
  outColor = mix(colDaz,colGoogle, 0.5);
  outColor = my_color;
}

