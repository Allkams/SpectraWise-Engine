#version 330 core
#extension GL_ARB_separate_shader_objects : enable
layout (location=0) in vec3 aPos;
layout (location=1) in vec4 color;
layout (location=2) in vec2 texture;

layout (location=0) out vec4 Color;

void main()
{
	gl_Position = vec4(aPos, 1.0f);
	Color = color;
}