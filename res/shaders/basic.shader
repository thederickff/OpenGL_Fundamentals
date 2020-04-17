#shader vertex
#version 450 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TextCoord;

uniform mat4 u_MVP;

void main()
{
    gl_Position = u_MVP * position;
    v_TextCoord = texCoord;
}

#shader fragment
#version 450 core

layout(location = 0) out mediump vec4 color;

in mediump vec2 v_TextCoord;

// uniform mediump vec4 u_Color;
uniform mediump sampler2D u_Texture;

void main()
{
    mediump vec4 textColor = texture(u_Texture, v_TextCoord);
    color = textColor;
    // color = u_Color;
}