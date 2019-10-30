#version 450 core

in vec2 Position; 
in vec2 Texcoord;

out vec2 varying_texcoord;

uniform float size;

void main(void) 
{ 
  gl_Position = vec4(size * Position, 0.0, 1.0);
  varying_texcoord = Texcoord;
} 

