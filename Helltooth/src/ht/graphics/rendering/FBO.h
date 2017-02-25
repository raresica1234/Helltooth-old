#pragma once

#include <GL/glew.h>

#include <vector>

#include "utils/memory/MemoryManager.h"

#include "../textures/Texture.h"
#include "../textures/TextureManager.h"

namespace ht { namespace graphics {

	class FBO {
	private:
		GLuint id;
		GLuint width, height;
		std::vector<unsigned int> textures;
		bool hasDepthBuffer = false;
		GLuint depthBuffer;

	public:
		FBO(GLuint width, GLuint height);
		~FBO();

		void createColorTexture();
		void createDepthTexture(bool texture);

		void bind();
		void unbind(int width, int height);

		inline GLuint getColorTexID() { return TextureManager::Get()->getTexture(textures[0])->getID(); }
		inline unsigned int getColorTexture() { return textures[0]; }
	};

} }
