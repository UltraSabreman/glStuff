#version 330 
 
layout(location = 0) in vec4 vert; 
layout(location = 3) in vec4 Color; 
 
out vec4 outCol; 
 
uniform mat4 projection; 
uniform mat4 modelview; 
 
void main() 
{ 
    gl_Position = projection * modelview * vert; 
	if (Color.x == 0.0) { 
		outCol += vec4(1.0,0.0,0.0,1.0); 
	}
    if (Color.y == 0.0) { 
		outCol += vec4(0.0,1.0,0.0,1.0); 
	} 
    if (Color.z == 0.0) {
		outCol += vec4(0.0,0.0,1.0,1.0); 
    }
 
	//outCol = Color; 
}