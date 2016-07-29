#pragma once

#include <GL/glew.h>
#include "../textures/Texture.h"
#include "../../utils/memory/MemoryManager.h"

#include <vector>
namespace ht { namespace graphics {

	class FBO {
	private:
		GLuint id;
		GLuint width, height;
		std::vector<Texture*> textures;
		bool hasDepthBuffer = false;
		GLuint depthBuffer;

	public:
		FBO(GLuint width, GLuint height);
		~FBO();

		void createColorTexture();
		void createDepthTexture(bool texture);

		void bind();
		void unbind(int width, int height);

		inline GLuint getColorTexID() { return textures[0]->getID(); }
		inline Texture* getColorTexture() { return textures[0]; }
	};

} }
