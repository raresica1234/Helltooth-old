#pragma once

#include "graphics/window/Window.h"
#include "graphics/window/WindowManager.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

namespace ht { namespace graphics {

	class GBuffer {
	private:
		std::vector<unsigned int> ids;

		GLuint fbo;

		GLuint textures[4]; // position, normal, diffuse, textcoord
		GLuint depthTexture;

		int width, height;

	public:
		GBuffer();
		~GBuffer();

		void bind();
		void unbind(const int &width, const int &height);
	};
} }
