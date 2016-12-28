#pragma once

#include "../Renderable.h"
#include "../../shaders/ShaderProgram.h"
#include "../Entity3D.h"

#include "../../../utils/memory/MemoryManager.h"

/*
DynamicRenderable component:
To be used when rendering dynamical entities
This component allows you to submit every frame and render every frame
*/

namespace ht { namespace graphics {

	class DynamicEntity : public Entity3D {

	public:
		Renderable* renderable;

	public:
		DynamicEntity(): Entity3D(), renderable(nullptr) { }

		DynamicEntity(Renderable* renderable)
			: renderable(renderable), Entity3D() { }

		DynamicEntity(Renderable* renderable, ht::maths::vec3 position)
			: renderable(renderable), Entity3D(position) { }

		DynamicEntity(Renderable* renderable, float x, float y, float z)
			: renderable(renderable), Entity3D(x, y, z) {}

		~DynamicEntity() {
			del renderable;
		}

		friend bool operator==(DynamicEntity left, DynamicEntity& right) {
			if ((Entity3D)left == (Entity3D)right) {
				return true;
			}
			return false;
		}

		inline Renderable* getRenderable() const {
			return renderable;
		}
	};
} }