#pragma once

#include <GL/glew.h>

#include <vector>

#include "utils/memory/MemoryManager.h"

#include "../textures/Texture.h"
#include "../textures/TextureManager.h"

namespace ht { namespace graphics {

	class FBO {
	private:
		uint32 id, width, height, depthBuffer;

		std::vector<uint32> textures;
		bool hasDepthBuffer = false;

	public:
		FBO(uint32 width, uint32 height);
		~FBO();

		void createColorTexture();
		void createDepthTexture(bool texture);

		void bind();
		void unbind(uint32 width, uint32 height);

		inline GLuint getColorTexID() { return TextureManager::Get()->getTexture(textures[0])->getID(); }
		inline unsigned int getColorTexture() { return textures[0]; }
	};

} }
