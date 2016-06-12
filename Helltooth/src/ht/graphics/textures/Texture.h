#pragma once

#include <FreeImage/FreeImage.h>
#include <GL/glew.h>

#include "../../utils/memory/MemoryManager.h"

namespace ht{ namespace graphics {

	class Texture {
	private:
		GLuint textureID;

	public:
		Texture();
		~Texture() {
			glDeleteTextures(1, &textureID);
		}

		inline void bind() const { glBindTexture(GL_TEXTURE_2D, textureID); }
		inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

		bool loadPixelArray(BYTE *pixels, GLsizei width, GLsizei height, long long bpp, unsigned int pixelSize) const;

		inline GLuint getID() const { return textureID; }

	};

} }