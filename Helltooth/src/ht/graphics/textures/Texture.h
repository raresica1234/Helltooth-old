#pragma once

#include <GL/glew.h>
#include <FreeImage/FreeImage.h>

#include "../../utils/memory/MemoryManager.h"

namespace ht{ namespace graphics {

	class Texture {
	private:
		GLuint textureID;

	public:
		Texture();
		~Texture() {

		}

		inline void bind() { glBindTexture(GL_TEXTURE_2D, textureID); }
		inline void unbind() { glBindTexture(GL_TEXTURE_2D, 0); }

		bool loadPixelArray(BYTE *pixels, GLsizei width, GLsizei height, long long bpp, unsigned int pixelSize);

		inline GLuint getID() { return textureID; }

	};

} }