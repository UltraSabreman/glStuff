#version 330

layout(location = 0) in vec4 vert;
layout(location = 3) in vec4 inCol;

out vec4 outCol;

uniform mat4 projection;
uniform mat4 modelview;

void main()
{
    gl_Position = projection * modelview * vert;
	outCol = inCol;
}