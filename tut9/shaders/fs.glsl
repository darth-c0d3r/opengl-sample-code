#version 400

in vec4 color;
in vec2 v_tex_coord;

out vec4 frag_color;
uniform sampler2D uTexture;

void main () 
{
  vec4 texColor = texture(uTexture, v_tex_coord);
  // frag_color = texColor;
  frag_color = color;
}
