#pragma once

#include "../Renderable.h"
#include "../../shaders/ShaderProgram.h"
#include "../Entity3D.h"

#include "../../Camera.h"

#include "../../../utils/memory/MemoryManager.h"
/*
StaticRenderable component:
To be used when rendering statical entities
This component allows you to submit once, but render every frame.
*/

namespace ht { namespace graphics {

	class StaticEntity : public Entity3D {

	protected:
		Renderable* renderable;
		bool hasShader = false;

	public:
		StaticEntity() : Entity3D(), renderable(nullptr) { }

		StaticEntity(Renderable* renderable)
			: renderable(renderable), Entity3D() { }

		StaticEntity(Renderable* renderable, vec3 position)
			: renderable(renderable), Entity3D(position) { }

		StaticEntity(Renderable* renderable, float x, float y, float z)
			: renderable(renderable), Entity3D(x, y, z) {}

		virtual void prepare() const {
			renderable->prepare();
		};

		virtual void setViewMatrix(const Camera* camera) const {
		};

		virtual void setProjection(mat4 projection) const {};
		
		virtual void setModelMatrix() const {};

		virtual ~StaticEntity() {
			del renderable;
		};

		virtual void render() const {
			renderable->render();
		};

		friend bool operator==(StaticEntity left, StaticEntity& right) {
			if ((Entity3D)left == (Entity3D)right) {
				return true;
			}
			return false;
		}

		inline void end() const {
			renderable->end();
		}

		inline bool hasOwnShader() const { return hasShader; }


	};

} }
