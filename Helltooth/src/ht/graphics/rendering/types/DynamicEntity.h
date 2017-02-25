#pragma once

#include "../Renderable.h"
#include "../Entity.h"

#include "../../shaders/ShaderProgram.h"

#include "utils/memory/MemoryManager.h"

/*
DynamicRenderable component:
To be used when rendering dynamical entities
This component allows you to submit every frame and render every frame
*/

namespace ht { namespace graphics {

	class DynamicEntity : public Entity {

	public:
		Renderable* renderable;

	public:
		DynamicEntity() : Entity(), renderable(nullptr) { this->type = DYNAMIC_ENTITY; }

		DynamicEntity(Renderable* renderable)
			: renderable(renderable), Entity() { this->type = DYNAMIC_ENTITY; }

		DynamicEntity(Renderable* renderable, ht::maths::vec3 position)
			: renderable(renderable), Entity(position) { this->type = DYNAMIC_ENTITY; }

		DynamicEntity(Renderable* renderable, float x, float y, float z)
			: renderable(renderable), Entity(x, y, z) { this->type = DYNAMIC_ENTITY; }

		~DynamicEntity() {
			del renderable;
		}

		friend bool operator==(DynamicEntity left, DynamicEntity& right) {
			if ((Entity)left == (Entity)right) {
				return true;
			}
			return false;
		}

		inline Renderable* getRenderable() const {
			return renderable;
		}
	};
} }