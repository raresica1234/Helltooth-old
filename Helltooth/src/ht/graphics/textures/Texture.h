#pragma once

#include <GL/glew.h>
#include "utils/memory/MemoryManager.h"

#include <FreeImage/FreeImage.h>

#include "utils/Internal.h"

namespace ht { namespace graphics {

	#define TEXTURE_COLOR_ATTACHMENT GL_RGB
	#define TEXTURE_DEPTH_ATTACHMENT GL_DEPTH_COMPONENT32

	class Texture {
	private:
		//texture ID
		uint32 textureID;

	public:
		//Constructor
		Texture();
		Texture(uint16 width, uint16 height, byte bpp);

		//Deconstrucotr
		__forceinline ~Texture() { glDeleteTextures(1, &textureID); }

		void setPixels(void* pixels, uint16 width, uint16 height, byte bpp);

		//loading textures
		bool loadPixelArray(byte *pixels, uint16 width, uint16 height, byte bpp, int32 wrap = GL_REPEAT, int32 mipmap = GL_LINEAR_MIPMAP_LINEAR) const;
		void createAttachment(uint16 width, uint16 height, uint16 type);
		void createGBufferTexture(uint16 width, uint16 height);

		//Basic tasks
		__forceinline void bind() const { glBindTexture(GL_TEXTURE_2D, textureID); }
		__forceinline void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }

		//getting id
		__forceinline uint32 getID() const { return textureID; }
	};
} }