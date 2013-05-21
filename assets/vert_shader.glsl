#version 330

layout(location = 0) in vec4 vert;
in vec3 inCol;

out vec3 outCol;

uniform mat4 projection;
uniform mat4 modelview;

void main()
{
    gl_Position = projection * modelview * vert;
	outCol = inCol;//vec3(1.0,0,0);
}