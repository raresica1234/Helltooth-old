#include "BatchRenderer2D.h"

namespace ht { namespace graphics {
	using namespace maths;
	using namespace utils;

	BatchRenderer2D::BatchRenderer2D() {
		init();
	}

	BatchRenderer2D::~BatchRenderer2D() {
		del ibo;
		glDeleteBuffers(1, &vbo);
	}

	void BatchRenderer2D::begin() {
		vao.bindVAO();
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
	}


	void BatchRenderer2D::submitTexture(float id) {
		unsigned int tid;
		if (id  > 0.5) {
			bool found = false;
			for (unsigned int i = 0; i < tids.size(); i++)
				if (tids[i] == id) {
					found = true;
					tid = i + 1;
				}
			if (!found) {
				if (tids.size() >= RENDERER_MAX_TEXTURES) {
					end();
					render();
					begin();
				}
				tids.push_back(id);
				tid = tids.size();
			}
		}
	}

	void BatchRenderer2D::submit(Sprite* e) {
		submitTexture(e->textureID);
		maths::vec4 sprite = e->data;

		buffer->position = maths::vec3(sprite.x - sprite.z, sprite.y - sprite.w, 1);
		buffer->uv = e->uvs[0];													 
		buffer->textureID = e->textureID;										 
		buffer->color = e->color;												 
		buffer++;																 
																				 
		buffer->position = maths::vec3(sprite.x - sprite.z, sprite.y + sprite.w, 1);
		buffer->uv = e->uvs[1];													 
		buffer->textureID = e->textureID;										 
		buffer->color = e->color; 												 
		buffer++;																 
																				 
		buffer->position = maths::vec3(sprite.x + sprite.z, sprite.y + sprite.w, 1);
		buffer->uv = e->uvs[2];													 
		buffer->textureID = e->textureID;										 
		buffer->color = e->color;												 
		buffer++;																 
																				 
		buffer->position = maths::vec3(sprite.x + sprite.z, sprite.y - sprite.w, 1);
		buffer->uv = e->uvs[3];
		buffer->textureID = e->textureID;
		buffer->color = e->color;
		buffer++;
		
		indexCount += 6;
	}

	void BatchRenderer2D::submitText(String text, float x, float y, vec4 color) {
		Font f = FontManager::Get()->getFont();
		unsigned int id = f.texture->getID();
		submitTexture(id);

		float xPos = x;
		float yPos = y;
		
		int r = color.x * 255.0f;
		int g = color.y * 255.0f;
		int b = color.z * 255.0f;
		int a = color.w * 255.0f;
		unsigned int col = a << 24 | b << 16 | g << 8 | r;

		unsigned int size = f.size;

		for (int i = 0; i < text.size; i++) {
			Glyph g = f.glyphs[text[i]];
			vec4 uv = g.uv;

			float xa = xPos + g.offset.x;
			float ya = yPos - g.offset.y;

			buffer->position = vec3(xa, ya, 1);
			buffer->color = col;
			buffer->uv = vec2(uv.x, uv.z);
			buffer->textureID = id;
			buffer++;

			buffer->position = vec3(xa + size, ya, 1);
			buffer->color = col;
			buffer->uv = vec2(uv.y, uv.z);
			buffer->textureID = id;
			buffer++;

			buffer->position = vec3(xa + size, ya + size, 1);
			buffer->color = col;
			buffer->uv = vec2(uv.y, uv.w);
			buffer->textureID = id;
			buffer++;

			buffer->position = vec3(xa, ya + size, 1);
			buffer->color = col;
			buffer->uv = vec2(uv.x, uv.w);
			buffer->textureID = id;
			buffer++;

			indexCount += 6;

			xPos += g.advance.x;
		}

	}

	void BatchRenderer2D::end() {
		glUnmapBuffer(GL_ARRAY_BUFFER);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void BatchRenderer2D::render() {
		for (unsigned int i = 0; i < tids.size(); i++) {
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, tids[i]);
		}

		vao.bindVAO();
		ibo->bindIBO();

		glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, NULL);

		ibo->unbindIBO();
		vao.unbindVAO();
		indexCount = 0;
		tids.clear();
	}


	void BatchRenderer2D::init() {
		glGenBuffers(1, &vbo);
		
		vao.bindVAO();
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
		glEnableVertexAttribArray(SHADER_UV_INDEX);
		glEnableVertexAttribArray(SHADER_TID_INDEX);
		glEnableVertexAttribArray(SHADER_COLOR_INDEX);

		glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
		glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(3 * sizeof(GLfloat)));
		glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(5 * sizeof(GLfloat)));
		glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(6 * sizeof(GLfloat)));


		GLushort* indices = htnew GLushort[RENDERER_INDICES_SIZE];

		short offset = 0;

		for (int i = 0; i < RENDERER_INDICES_SIZE; i+=6) {
			indices[  i  ] = offset + 0;
			indices[i + 1] = offset + 1;
			indices[i + 2] = offset + 2;

			indices[i + 3] = offset + 2;
			indices[i + 4] = offset + 3;
			indices[i + 5] = offset + 0;
			offset += 4;
		}

		ibo = htnew IBO();
		ibo->bindIBO();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, RENDERER_INDICES_SIZE * sizeof(GLushort), indices, GL_STATIC_DRAW);

		ibo->unbindIBO();

		vao.unbindVAO();
	}


} }