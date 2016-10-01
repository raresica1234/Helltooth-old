#pragma once

#include "../rendering/model/RawModel.h"
#include "../../maths/vec3.h"
#include "../../maths/vec2.h"

#include "../rendering/Renderable.h"
#include "../rendering/types/StaticEntity.h"

#include "../Camera.h"

#include <vector>
namespace ht { namespace graphics {

#define VERTEX_COUNT 128
#define TERRAIN_SIZE 800

	class Terrain : public StaticEntity {
	private:
		ShaderProgram* program;
		
	public:
		Terrain(maths::vec2 location);

		~Terrain();

		void prepare() const {
			renderable->prepare();
			program->start();
		}

		void setModelMatrix() const override {
			mat4 model = getModelMatrix();
			program->uniformMat4("modelMatrix", model);
			program->stop();
		}
		void setProjection(mat4 projection) const override {
			program->start();
			program->uniformMat4("projectionMatrix", projection);
		}

		void setViewMatrix(const Camera *camera) const override {
			program->uniformMat4("viewMatrix", camera == nullptr ? mat4::createIdentity() : camera->generateViewMatrix());
		}

		void render() const {
			renderable->render();
			program->stop();
			renderable->end();
		}

	};
} }
