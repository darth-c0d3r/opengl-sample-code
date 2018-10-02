#version 400

in vec3 vPosition;
out vec4 color;

void main () 
{
  gl_Position = vec4(vPosition, 1.0);
  color = vec4(0.1,0.2,0.4,1.0);
}
