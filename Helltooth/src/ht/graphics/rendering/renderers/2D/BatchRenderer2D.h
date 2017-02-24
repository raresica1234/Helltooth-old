#pragma once

#include "../Renderer.h"
#include "../../../textures/Texture.h"
#include "../../../textures/TextureManager.h"
#include "../../Vertex.h"

#include "graphics/ui/font/FontManager.h"

#include "../../2D/Sprite.h"

#include "maths/mat3.h"

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

		std::vector<maths::mat3> transformationStack;

		maths::mat3* transformationBack = nullptr;

		std::vector<float> tids;
	public:
		BatchRenderer2D();
		~BatchRenderer2D();

		void begin();
		void submit(Sprite* e);
		void end();
		void render();

		void submitText(utils::String text, float x, float y, unsigned int color);
		void submitText(utils::String text, float x, float y, maths::vec4 color);

		__forceinline void push(maths::mat3& matrix, bool override = false) {
			if (override)
				transformationStack.push_back(matrix);
			else
				transformationStack.push_back(transformationStack.back() * matrix);

			transformationBack = &transformationStack.back();
		}

		__forceinline void pop() {
			if (transformationStack.size() > 1)
				transformationStack.pop_back();
			else
				HT_WARN("[BatchRenderer2D] Can not pop matrix from transformation stack. Transformation Stack empty.");

			transformationBack = &transformationStack.back();
		}

	private:
		void init();
		unsigned int submitTexture(float id);
	};



} }

