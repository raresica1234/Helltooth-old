R"(#version 330 core

in vec2 textureCoord;
in vec4 color;
in float texID;

uniform sampler2D textures[32];

out vec4 out_color;

void main() {
	if(texID > 0.5) {
		highp int tex = int(texID);
		out_color = color;
		float text = texture(textures[tex - 1], textureCoord).a;
		if(text > 0.5)
			out_color.w = 1.0;
		else
			out_color.w = 0.0;

	} else {
		out_color = color;
	}
}
)"