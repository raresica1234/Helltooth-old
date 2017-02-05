#include "BatchRenderer2D.h"

namespace ht { namespace graphics {
	using namespace maths;
	using namespace utils;

	BatchRenderer2D::BatchRenderer2D() {
		transformationStack.push_back(mat4::createIdentity());
		transformationBack = &transformationStack.back();

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


	unsigned int BatchRenderer2D::submitTexture(float id) {
		unsigned int tid = 0;
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

		return tid;
	}

	void BatchRenderer2D::submit(Sprite* e) {
		unsigned int tid = submitTexture(e->textureID);
		maths::vec4 sprite = e->data;

		buffer->position = *transformationBack * maths::vec3(sprite.x - sprite.z, sprite.y - sprite.w, 1);
		buffer->uv = e->uvs[0];
		buffer->textureID = tid;
		buffer->color = e->color;
		buffer++;
		
		buffer->position = *transformationBack * maths::vec3(sprite.x - sprite.z, sprite.y + sprite.w, 1);
		buffer->uv = e->uvs[1];
		buffer->textureID = tid;
		buffer->color = e->color;
		buffer++;
		
		buffer->position = *transformationBack * maths::vec3(sprite.x + sprite.z, sprite.y + sprite.w, 1);
		buffer->uv = e->uvs[2];													 
		buffer->textureID = tid;
		buffer->color = e->color;												 
		buffer++;																 
		
		buffer->position = *transformationBack * maths::vec3(sprite.x + sprite.z, sprite.y - sprite.w, 1);
		buffer->uv = e->uvs[3];
		buffer->textureID = tid;
		buffer->color = e->color;
		buffer++;
		
		indexCount += 6;
	}

	void BatchRenderer2D::submitText(String text, float x, float y, vec4 color) {
		Font& f = FontManager::Get()->getFont();

		unsigned int tid = submitTexture(f.atlas->id);

		ftgl::texture_font_t* ftFont = f.font;

		maths::vec2 scale = vec2(1, 1);

		int r = color.x * 255.0f;
		int g = color.y * 255.0f;
		int b = color.z * 255.0f;
		int a = color.w * 255.0f;

		unsigned int col = a << 24 | b << 16 | g << 8 | r;

		for (unsigned int i = 0; i < text.size - 1; i++) {
			char c = text[i];
			ftgl::texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);

			if (glyph) {
				if (i > 0) {
					float kerning = ftgl::texture_glyph_get_kerning(glyph, text[i - 1]);
					x += kerning / scale.x;
				}

				if (c == '\n') {
					y -= (glyph->advance_y > 0.0f ? glyph->advance_y : (glyph->height + (f.size + 6) / 3)) / scale.y;
					x = x;
					continue;
				}
				

				float x0 = x  + glyph->offset_x;
				float y0 = y  + glyph->offset_y;
				float x1 = x0 + glyph->width;
				float y1 = y0 - glyph->height;

				float u0 = glyph->s0;
				float v0 = glyph->t0;
				float u1 = glyph->s1;
				float v1 = glyph->t1;

				buffer->position = *transformationBack * maths::vec3(x0, y0, 0.1f);
				buffer->uv = maths::vec2(u0, v0);
				buffer->textureID = tid;
				buffer->color = col;
				buffer++;

				buffer->position = *transformationBack * maths::vec3(x0, y1, 0.1f);
				buffer->uv = maths::vec2(u0, v1);
				buffer->textureID = tid;
				buffer->color = col;
				buffer++;

				buffer->position = *transformationBack * maths::vec3(x1, y1, 0.1f);
				buffer->uv = maths::vec2(u1, v1);
				buffer->textureID = tid;
				buffer->color = col;
				buffer++;

				buffer->position = *transformationBack * maths::vec3(x1, y0, 0.1f);
				buffer->uv = maths::vec2(u1, v0);
				buffer->textureID = tid;
				buffer->color = col;
				buffer++;

				indexCount += 6;
				x += glyph->advance_x / scale.x;
			}
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