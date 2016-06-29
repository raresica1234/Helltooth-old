#pragma once

#include "../../utils/memory/MemoryManager.h"

#include <GL/glew.h>
#include <FreeImage/FreeImage.h>

namespace ht{ namespace graphics {

	class Texture {
	private:
		//texture ID
		GLuint textureID;

	public:
		//Constructor
		Texture();
		//Deconstrucotr
		~Texture() {
			glDeleteTextures(1, &textureID);
		}

		//Basic tasks
		inline void bind() const { glBindTexture(GL_TEXTURE_2D, textureID); }
		inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

		//loading textures
		bool loadPixelArray(BYTE *pixels, GLsizei width, GLsizei height, GLsizei bpp) const;

		//getting id
		inline GLuint getID() const { return textureID; }

	};

} }