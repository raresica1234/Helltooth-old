#pragma once

#include <list>
#include "../Renderer.h"

#include "graphics/ui/font/FontManager.h"

#include "graphics/textures/Texture.h"
#include "graphics/textures/TextureManager.h"

#include "graphics/rendering/Vertex.h"

#include "../../2D/Sprite.h"

#include "maths/mat3.h"


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

		std::vector<maths::mat4> transformationStack;

		maths::mat4* transformationBack = nullptr;

		std::vector<float> tids;
	public:
		BatchRenderer2D();
		~BatchRenderer2D();

		
		void begin();
		void submit(Sprite* e);
		void end();
		void render();

		void submitText(utils::String text, float x, float y, unsigned int color, maths::vec2 scale);
		void submitText(utils::String text, float x, float y, maths::vec4 color, maths::vec2 scale);

		__forceinline void push(maths::mat4& matrix, bool override = false) {
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

