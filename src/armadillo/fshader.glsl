#version 450 core

in vec2 varying_texcoord;

layout(location = 0) out vec4 out_color;

void main(void)
{
  out_color = vec4(varying_texcoord, 0.0, 1.0);
}

