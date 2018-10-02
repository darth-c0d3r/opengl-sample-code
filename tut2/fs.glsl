#version 400

out vec4 frag_colour_1;
out vec4 frag_colour_2;

void main () 
{
  frag_colour_1 = vec4 (0.5, 0.0, 0.5, 1.0);
  frag_colour_2 = vec4 (0.0, 0.0, 0.5, 1.0);
}
