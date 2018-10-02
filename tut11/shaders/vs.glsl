#version 400

in vec3 vPosition;
in vec4 vColor;
out vec4 color;

uniform mat4 vMVP;

void main () 
{
  gl_Position = vMVP * vec4(vPosition, 1.0);
  color = vColor;
}
