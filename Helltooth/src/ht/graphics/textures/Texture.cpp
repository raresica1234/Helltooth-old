#include "Texture.h"

namespace ht { namespace graphics {

	Texture::Texture() {
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
		HT_INFO("[Texture] Texture created with id %i", textureID);
	}

	Texture::Texture(uint16 width, uint16 height, byte bpp) {
		glGenTextures(1, &textureID);

		glBindTexture(GL_TEXTURE_2D, textureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		switch (bpp) {
		case 16:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE_ALPHA, width, height, 0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, NULL); break;

		case 24:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL); break;

		case 32:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL); break;
		}
	}

	bool Texture::loadPixelArray(byte *pixels, uint16 width, uint16 height, byte bpp, int32 wrap, int32 mipmap) const {
		glBindTexture(GL_TEXTURE_2D, textureID);
		switch (bpp) {
		case 24:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels); break;

		case 32:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels); break;
		}

		if(mipmap != GL_NEAREST)
			glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, mipmap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, (GLfloat)-0.4);

		unbind();
		return true;
	}

	void Texture::setPixels(void* pixels, uint16 width, uint16 height, byte bpp) {
		glBindTexture(GL_TEXTURE_2D, textureID);

		switch (bpp) {
		case 16:
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, pixels); break;

		case 24:
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels); break;

		case 32:
			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, pixels); break;
		}
	}

	void Texture::createAttachment(uint16 width, uint16 height, uint16 type) {
		glTexImage2D(GL_TEXTURE_2D, 0, type, width, height, 0, type == GL_RGB ? GL_RGB : GL_DEPTH_COMPONENT,
			type == GL_RGB ? GL_UNSIGNED_BYTE : GL_FLOAT, nullptr); 
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}

	void Texture::createGBufferTexture(uint16 width, uint16 height) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	}
} }