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
		uint32 fbo, width, height;

		std::vector<Texture*> textures;
		Texture* depth;

	public:
		GBuffer();
		~GBuffer();

		void bind();
		void unbind(const uint32 &width, const uint32 &height);

		__forceinline Texture* getTexture(uint32 id) { return textures[id]; }
		__forceinline Texture* getDepthTexture() { return textures[4]; }
		__forceinline uint32 getSize() { return textures.size(); }

		__forceinline void bindTextures() {
			for (uint32 i = 0; i < textures.size(); i++) { glActiveTexture(GL_TEXTURE0 + i); textures[i]->bind(); }
		}
	};
} }
