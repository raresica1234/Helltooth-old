R"(

#version 330 core

in vec2 textureCoordinates;

out vec4 color;

void main() {
	//color = texture(textures[0], textureCoordinates * tilingValue);
	color = vec4(1.0, 1.0, 1.0, 1.0);
}
)"