#version 330 
 
layout(location = 0) in vec4 vert; 
 
uniform mat4 projection; 
uniform mat4 modelview; 
 
void main() 
{ 
    gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * vert; 
	//lol
}