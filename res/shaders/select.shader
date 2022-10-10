#shader vertex
#version 330 core

in vec3 apos;
in vec2 abound;

out vec3 ourColor;
out vec2 ourBound;

uniform mat4 u_MVP;


void main() {
    gl_Position = u_MVP * vec4(apos, 1.0);
    ourBound = abound;
}

#shader fragment
#version 330 core

in vec2 ourBound;

uniform vec4 u_setColor;

void main() {
    float dist = sqrt((ourBound.x * ourBound.x) + (ourBound.y * ourBound.y));
    vec4 color_used = vec4(vec3(1.0), 0.0);
    if(dist < 1.0){
        color_used = u_setColor;
    }
    gl_FragColor = color_used;
}
