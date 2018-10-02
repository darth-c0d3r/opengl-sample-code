#version 400

in vec3 vPosition;
in vec2 vTexture;
in vec4 vColor;

out vec4 color;
out vec2 v_tex_coord;

void main () 
{
  gl_Position = vec4(vPosition, 1.0);
  color = vColor;
  v_tex_coord = vTexture;
}
