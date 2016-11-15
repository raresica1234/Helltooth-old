#pragma once


#include <unordered_map>

#include "../shaders/ShaderProgram.h"

#include "../rendering/types/StaticEntity.h"

#include "../rendering/Renderable.h"

#include "TerrainShader.h"

#include "../../utils/List.h"

namespace ht { namespace graphics {

#define TERRAIN_SIZE 800
#define VERTEX_COUNT 128

	class World : public StaticEntity {
	private: 
		List<Pair<vec2, Renderable*>> terrains;

		int terrainSize;

		TerrainShader shader;

		ShaderProgram* program;

	public:
		World(int size, vec4 terrainCounts);
		~World();

		vec2 isUnderTerrain(vec3 position) {
			vec2 player = vec2(position.x, position.z);
		}

		inline void prepare() const override {
			program->start();
		};

		inline void setViewMatrix(const Camera* camera) const override {
			program->uniformMat4("viewMatrix", camera->generateViewMatrix());
		};

		inline void setProjection(mat4 projection) const override {
			program->start();
			program->setProjection("projectionMatrix", projection);
			program->stop();
		};

		inline void setModelMatrix() const override {
		};

		inline void render() const override {
			for (int i = 0; i < terrains.size; i++) {
				Renderable * r = terrains[i].value;
				r->prepare();
				auto pair = terrains[i];
				mat4 model = mat4::createIdentity();
				vec2 position = pair.key;

				model.translate(vec3(position.x * TERRAIN_SIZE, 0.0, position.y * TERRAIN_SIZE));

				program->uniformMat4("modelMatrix", model);
				r->render();
				r->end();
			}
			program->stop();
		};


		__forceinline void addTexture(const Texture* texture) {
			for (int i = 0; i < terrains.size; i++) {
				Renderable *r = terrains[i].value;
				r->addTexture(texture);
			}
		}

	private:
		Renderable* generateTerrain();

	};


} }
