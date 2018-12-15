#shader vertex
#version 300 es

layout(location = 0) in vec4 position;

void main()
{
    gl_Position = position;
}

#shader fragment
#version 300 es

layout(location = 0) out mediump vec4 color;
uniform mediump vec4 u_Color;

void main()
{
    color = u_Color;
}