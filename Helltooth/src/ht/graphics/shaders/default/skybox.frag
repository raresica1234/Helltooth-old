R"(
#version 330 core

in DATA {
	vec3 position;
} fs_in;

uniform samplerCube skybox;

out vec4 color;

void main() {

	vec3 tCoord;
	if(fs_in.position.y == 1.0 || fs_in.position.y == -1.0){
		tCoord.x = fs_in.position.x;
		tCoord.y = fs_in.position.y;
		tCoord.z = fs_in.position.z;
	}
	else{
		tCoord.x = -fs_in.position.x;
		tCoord.y = -fs_in.position.y;
		tCoord.z = fs_in.position.z;
	}

	color = texture(skybox, tCoord);
}
)"