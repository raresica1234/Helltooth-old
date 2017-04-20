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
		std::vector<unsigned int> ids;

		GLuint fbo;

		std::vector<Texture*> textures;

		int width, height;

	public:
		GBuffer();
		~GBuffer();

		void bind();
		void unbind(const int &width, const int &height);

		Texture* operator[](unsigned int id) { return textures[id]; }
		__forceinline Texture* getDepthTexture() { return textures[4]; }

		__forceinline unsigned int getSize() { return textures.size() - 1; }
	};
} }
