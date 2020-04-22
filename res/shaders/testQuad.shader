#shader vertex
#version 450 core

layout(location = 0) in vec4 position;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
}

#shader fragment
#version 450 core

layout(location = 0) out mediump vec4 color;

uniform mediump vec4 u_color;

void main()
{
    color = u_color;
}