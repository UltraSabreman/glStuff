#version 330

in vec3 outCol;
out vec4 fragColor;

void main()
{
    fragColor = vec4(outCol,1.0);
}