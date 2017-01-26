#pragma once

#include "../Renderer.h"
#include "../../../textures/Texture.h"
#include "../../../textures/TextureManager.h"
#include "../../Vertex.h"

#include "graphics/ui/font/FontManager.h"

#include "../../2D/Sprite.h"

#include <list>

namespace ht { namespace graphics {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(VertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES	32

#define SHADER_VERTEX_INDEX		0
#define SHADER_UV_INDEX			1
#define SHADER_TID_INDEX		2
#define SHADER_COLOR_INDEX		3

	class BatchRenderer2D {
	private:
		VAO vao;
		IBO* ibo;
		GLuint vbo;
		GLsizei indexCount;
		
		VertexData* buffer;

		std::vector<float> tids;
	public:
		BatchRenderer2D();
		~BatchRenderer2D();

		void begin();
		void submit(Sprite* e);
		void end();
		void render();

		void submitText(utils::String text, float x, float y, maths::vec4 color);

	private:
		void init();
		unsigned int submitTexture(float id);
	};



} }

