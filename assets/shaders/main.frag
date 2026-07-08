#version 330 core

in vec4 v_color;
in vec2 v_texCoords;
flat in int v_texIndex;

out vec4 frag_color;
uniform sampler2D u_textures[16];

void main() {
  frag_color = texture(u_textures[v_texIndex], v_texCoords) * v_color;  
}
