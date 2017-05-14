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
		f32 textureID;
		uint32 color;
	};

	struct Sprite {
		maths::vec4 data;
		maths::vec2 uvs[4];

		union {
			f32 textureID;
			uint32 color;
		};

		bool hasTexture = false;

		Sprite(f32 x, f32 y, f32 width, f32 height) {
			data = maths::vec4(x, y, width, height);

			uvs[0] = maths::vec2(0, 0);
			uvs[1] = maths::vec2(0, 1);
			uvs[2] = maths::vec2(1, 1);
			uvs[3] = maths::vec2(1, 0);
		}

		Sprite* setColor(maths::vec4 color) {
			int32 r = (int32)(color.x * 255.0f);
			int32 g = (int32)(color.y * 255.0f);
			int32 b = (int32)(color.z * 255.0f);
			int32 a = (int32)(color.w * 255.0f);

			uint32 col = a << 24 | b << 16 | g << 8 | r;
			setColor(col);
			return this;
		}
		
		__forceinline Sprite* setColor(uint32 color) { this->color = color; hasTexture = false; return this; }
		__forceinline Sprite* setTexture(const Texture* texture) { textureID = texture->getID(); hasTexture = true; return this; }
	};
} }