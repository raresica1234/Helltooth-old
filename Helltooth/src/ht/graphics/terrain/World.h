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
			float height = getHeight(player.x, player.y, (float)TERRAIN_SIZE / ((float)VERTEX_COUNT - 1));
			if (height > position.y)
				return true;
			return false;
		}

		inline void prepare() const override {
			program->start();
		};

		inline void setViewMatrix(maths::mat4 camera) const override {
			program->uniformMat4("viewMatrix", camera);
			program->uniform1f("density", API::getFog().density);
			program->uniform1f("gradient", API::getFog().gradient);
			program->uniform4f("skyColor", maths::vec4(.3f, .4f, .7f, 1.f));
		};

		inline void setProjection(ht::maths::mat4 projection) const override {
			if (program->hasProjection())
				return;
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


				maths::mat4 model = maths::mat4().translate(entry.position.x * TERRAIN_SIZE, 0.0, entry.position.y * TERRAIN_SIZE);

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
