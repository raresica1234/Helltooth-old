#pragma once

#include <GL/glew.h>

#include "maths/vec2.h"
#include "maths/vec3.h"
#include "maths/vec4.h"

#include "graphics/textures/Texture.h"

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

		union {
			struct {
				float textureID;
			};
			struct {
				unsigned int color;
			};
		};

		bool hasTexture = false;

		Sprite(float x, float y, float width, float height) {
			data = maths::vec4(x, y, width, height);

			uvs[0] = maths::vec2(0, 0);
			uvs[1] = maths::vec2(0, 1);
			uvs[2] = maths::vec2(1, 1);
			uvs[3] = maths::vec2(1, 0);
		}

		Sprite* setColor(maths::vec4 color) {
			int r = (int)(color.x * 255.0f);
			int g = (int)(color.y * 255.0f);
			int b = (int)(color.z * 255.0f);
			int a = (int)(color.w * 255.0f);

			unsigned int col = a << 24 | b << 16 | g << 8 | r;
			setColor(col);
			return this;
		}
		
		Sprite* setColor(unsigned int color) {
			this->color = color;
			hasTexture = false;
			return this;
		}

		Sprite* setTexture(const Texture* texture) {
			textureID = texture->getID();
			hasTexture = true;
			return this;
		}
	};
} }