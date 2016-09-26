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

		void prepare(ShaderProgram* program) const {
			this->program->start();
			renderable->prepare(this->program);
			this->program->stop();
		}

		void setModelMatrix() const {
			program->start();
			program->uniformMat4("modelMatrix", mat4::createIdentity());
			program->stop();
		}
		void setProjection(mat4 projection) const {
			program->start();
			program->uniformMat4("projectionMatrix", mat4::createIdentity()); 
			program->stop();
		}

		void setViewMatrix(const Camera *camera) const {
			program->start();
			program->uniformMat4("viewMatrix", mat4::createIdentity()/*camera == nullptr ? mat4::createIdentity() : camera->generateViewMatrix()*/);
			program->stop();
		}

		void render() const {
			program->start();
			renderable->render();
			program->stop();
			renderable->end();
		}

	};
} }
