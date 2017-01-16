#pragma once

#include "../Renderable.h"
#include "../../shaders/ShaderProgram.h"
#include "../Entity.h"

#include "../../Camera.h"

#include "../../../utils/memory/MemoryManager.h"
/*
StaticRenderable component:
To be used when rendering statical entities
This component allows you to submit once, but render every frame.
*/
namespace ht { namespace graphics {

	class StaticEntity : public Entity {

	protected:
		Renderable* renderable = nullptr;
		bool hasShader = false;

	public:
		StaticEntity() : Entity(), renderable(nullptr) { this->type = STATIC_ENTITY; }

		StaticEntity(Renderable* renderable)
			: renderable(renderable), Entity() { this->type = STATIC_ENTITY; }

		StaticEntity(Renderable* renderable, maths::vec3 position)
			: renderable(renderable), Entity(position) { this->type = STATIC_ENTITY; }

		StaticEntity(Renderable* renderable, float x, float y, float z)
			: renderable(renderable), Entity(x, y, z) { this->type = STATIC_ENTITY; }

		virtual void prepare() const {
			if(renderable)
				renderable->prepare();
		};

		virtual void setViewMatrix(maths::mat4 camera) const {
		};

		virtual void setProjection(maths::mat4 projection) const {};
		
		virtual void setModelMatrix() const {};

		virtual ~StaticEntity() {
			if(renderable)
				del renderable;
		};

		virtual void render() const {
			renderable->render();
		};

		friend bool operator==(const StaticEntity left, const StaticEntity& right) {
			if ((Entity)left == (Entity)right) {
				return true;
			}
			return false;
		}

		inline void end() const {
			if (renderable)
				renderable->end();
		}

		inline bool hasOwnShader() const { return hasShader; }

	};
} }
