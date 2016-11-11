#pragma once


#include <unordered_map>

#include "../shaders/ShaderProgram.h"

#include "../rendering/types/StaticEntity.h"

#include "../rendering/Renderable.h"

#include "TerrainShader.h"

namespace ht { namespace graphics {

#define TERRAIN_SIZE 800
#define VERTEX_COUNT 128

	class World : public StaticEntity {
	private: 
		std::unordered_map<vec2, Renderable*> terrains;
		
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
			for (auto entry : terrains) {
				entry.second->prepare();
			}
		};

		inline void setViewMatrix(const Camera* camera) const override {
			program->uniformMat4("viewMatrix", camera->generateViewMatrix());
		};

		inline void setProjection(mat4 projection) const override {
			program->setProjection("projectionMatrix", projection);
		};

		inline void setModelMatrix() const override {
			for (auto entry : terrains) {
				mat4 model = mat4::createIdentity();
				vec2 position = entry.first;
				model.translate(vec3(position.x, 0.0f, position.y));
				model.scale(vec3(1, 1, 1));

				program->uniformMat4("modelMatrix", model);
			}
		};

		inline void render() const override {
			for (auto entry : terrains) {
				entry.second->render();
			}
		};


	private:
		Renderable* generateTerrain();

	};


} }
