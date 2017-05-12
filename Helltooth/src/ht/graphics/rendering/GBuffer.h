#pragma once

#include "graphics/window/Window.h"
#include "graphics/window/WindowManager.h"

#include "graphics/textures/Texture.h"
#include "graphics/textures/TextureManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

namespace ht { namespace graphics {

	class GBuffer {
	private:
		GLuint fbo;

		std::vector<Texture*> textures;
		Texture* depth;

		int width, height;

	public:
		GBuffer();
		~GBuffer();

		void bind();
		void unbind(const int &width, const int &height);

		Texture* getTexture(unsigned int id) { return textures[id]; }
		__forceinline Texture* getDepthTexture() { return textures[4]; }

		unsigned int getSize() { return textures.size(); }

		__forceinline void bindTextures() {
			for (int i = 0; i < textures.size(); i++) {
				glActiveTexture(GL_TEXTURE0 + i);
				textures[i]->bind();
			}
		}
	};
} }
