#version 450 core

in vec2 varying_texcoord;

out vec4 out_color;

void main(void)
{
  gl_FragColor = vec4(varying_texcoord, 0.0, 1.0);
}

