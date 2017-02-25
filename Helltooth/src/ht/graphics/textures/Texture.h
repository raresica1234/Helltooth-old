#pragma once

#include <GL/glew.h>
#include "utils/memory/MemoryManager.h"

#include <FreeImage/FreeImage.h>

namespace ht { namespace graphics {

	#define TEXTURE_COLOR_ATTACHMENT GL_RGB
	#define TEXTURE_DEPTH_ATTACHMENT GL_DEPTH_COMPONENT32

	class Texture {
	private:
		//texture ID
		GLuint textureID;

	public:
		//Constructor
		Texture();
		Texture(unsigned int width, unsigned int height, unsigned int bpp);

		//Deconstrucotr
		inline ~Texture() {
			glDeleteTextures(1, &textureID);
		}

		//Basic tasks
		inline void bind() const { glBindTexture(GL_TEXTURE_2D, textureID); }
		inline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

		void setPixels(void* pixels, unsigned int width, unsigned int height, unsigned int bpp);

		//loading textures
		bool loadPixelArray(BYTE *pixels, GLsizei width, GLsizei height, GLsizei bpp, int wrap = GL_REPEAT, int mipmap = GL_LINEAR_MIPMAP_LINEAR) const;

		void createAttachment(int width, int height, int type);

		//getting id
		inline GLuint getID() const { return textureID; }

	};

} }