#version 330 core

layout(location=0) in vec2 a_pos;
layout(location=1) in vec2 a_texCoords;
layout(location=2) in float a_texIndex;
layout(location=3) in vec4 a_color;

out vec4 v_color;
out vec2 v_texCoords;
flat out int v_texIndex;

uniform mat4 u_proj;
uniform mat4 u_view;

void main()
{
    v_color = a_color;
    v_texCoords = a_texCoords;
    v_texIndex = int(a_texIndex);

    gl_Position = u_proj * vec4(a_pos, 0.0, 1.0);
}


