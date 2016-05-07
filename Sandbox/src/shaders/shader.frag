#version 400 core

in vec3 positions;


out vec4 color;

void main(){
	//color = vec4(1.0, 1.0, 1.0, 1.0);
	color = vec4(positions.x + 0.3, positions.y + 0.2, positions.z + 0.3, 1.0);
} 