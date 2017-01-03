#pragma once

#include <vector>

#include "../shaders/ShaderProgram.h"
#include "../rendering/types/StaticEntity.h"
#include "../rendering/Renderable.h"
#include "TerrainShader.h"
#include "../textures/TextureManager.h"

namespace ht { namespace graphics {

	#define TERRAIN_SIZE 800
	#define VERTEX_COUNT 128

	struct Chunk {
		ht::maths::vec2 position;
		Renderable* chunk;

		Chunk() { chunk = nullptr; }
		Chunk(ht::maths::vec2 position, Renderable* chunk) : position(position), chunk(chunk) {}
	};

	class World : public StaticEntity {
	private: 
		std::vector<Chunk> chunks;

		int terrainSize;

		TerrainShader shader;

		ShaderProgram* program;

		friend struct PerlinNoise;

	public:
		World(int size, ht::maths::vec4 terrainCounts);
		~World();

		bool isUnderTerrain(ht::maths::vec3 position) {
			ht::maths::vec2 player = ht::maths::vec2(position.x, position.z);
			return true;
		}

		inline void prepare() const override {
			program->start();
		};

		inline void setViewMatrix(const Camera* camera) const override {
			program->uniformMat4("viewMatrix", camera->generateViewMatrix());
		};

		inline void setProjection(ht::maths::mat4 projection) const override {
			program->start();
			program->setProjection("projectionMatrix", projection);
			program->stop();
		};

		inline void setModelMatrix() const override {
		};

		inline void render() const override {
			for (Chunk entry : chunks) {
				Renderable * r = entry.chunk;
				r->prepare();


				ht::maths::mat4 model = ht::maths::mat4::createIdentity();
				model.translate(ht::maths::vec3(entry.position.x * TERRAIN_SIZE, 0.0, entry.position.y * TERRAIN_SIZE));

				program->uniformMat4("modelMatrix", model);

				r->render();
				r->end();
			}
			program->stop();
		};


		__forceinline void addTexture(const Texture* texture) {
			for (Chunk entry : chunks) {
				Renderable *r = entry.chunk;
				r->addTexture(texture);
			}
		}

		__forceinline void addTexture(const unsigned int &id) {
			for (Chunk entry : chunks) {
				Renderable *r = entry.chunk;
				r->addTexture(id);
			}
		}

	private:
		maths::vec3 generateNormal(float x, float y, float distance);
		float getHeight(float x, float y, float distance);

		Renderable* generateTerrain();

	};
} }
