#include "Texture.h"

namespace ht { namespace graphics {

	Texture::Texture() {
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_2D, textureID);
	}

	bool Texture::loadPixelArray(BYTE *pixels, GLsizei width, GLsizei height, GLsizei bpp) const {
		switch (bpp)
		{
		case 24:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, pixels); break;

		case 32:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA, GL_UNSIGNED_BYTE, pixels); break;
		}


		glGenerateMipmap(GL_TEXTURE_2D);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, (GLfloat)-0.4);

		unbind();
		return true;
	}


} }