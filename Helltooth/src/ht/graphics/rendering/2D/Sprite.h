#pragma once

#include <GL/glew.h>

#include "../../../maths/vec2.h"
#include "../../../maths/vec3.h"
#include "../../../maths/vec4.h"

#include "../../textures/Texture.h"

namespace ht { namespace graphics {

	struct VertexData {
		maths::vec3 position;
		maths::vec2 uv;
		float textureID;
		unsigned int color;
	};

	struct Sprite {
		maths::vec4 data;
		maths::vec2 uvs[4];

		float textureID;
		unsigned int color;

		Sprite(float x, float y, float width, float height, maths::vec4 color) {
			int r = color.x * 255.0f;
			int g = color.y * 255.0f;
			int b = color.z * 255.0f;
			int a = color.w * 255.0f;

			unsigned int col = a << 24 | b << 16 | g << 8 | r;
			width = width / 2;
			height = height / 2;
			x += width;
			y += height;
			createSprite(x, y, width, height, col);
		}
		Sprite(float x, float y, float width, float height, const Texture* texture) {
			x += width / 2;
			y += height / 2;
			createSprite(x, y, width, height, texture->getID(), true);
		}

		~Sprite() {}

	private:
		void createSprite(float x, float y, float width, float height, unsigned int textureID, bool hasTexture = false) {
			if (hasTexture)
				this->textureID = textureID;
			else
				this->color = textureID;
			
			data = maths::vec4(x, y, width, height);
			
			uvs[0] = maths::vec2(0, 0);
			uvs[1] = maths::vec2(0, 1);
			uvs[2] = maths::vec2(1, 1);
			uvs[3] = maths::vec2(1, 0);
		}
	};


} }