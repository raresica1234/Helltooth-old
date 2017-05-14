#pragma once

#include "Renderable.h"

#include "maths/vec3.h"
#include "maths/mat4.h"

#include "utils/Internal.h"

namespace ht { namespace graphics {

	enum Type {
		STATIC_ENTITY,
		DYNAMIC_ENTITY,
		NO_TYPE
	};

	class Entity {
	protected:
		Type type = NO_TYPE;

		//Entity data
		maths::vec3 position, rotation, vscale;
		mutable maths::mat4 modelMatrix;

	public:

		//Constructor
		//Entity(positionX, positionY, positionZ)
		Entity(const f32 &x, const f32 &y, const f32 &z);

		//Default constructor
		//Sets everything to 0 (default) and the scale to 1
		Entity();

		Entity(const maths::vec3 position);

		void rotate(maths::vec3 &axis);

		void scale(const f32 &scaleX, const f32 &scaleY, const f32 &scaleZ);
		void scale(const maths::vec3 scale);

		void move(maths::vec3 &move);

		__forceinline maths::mat4 getModelMatrix() const { return modelMatrix; }
		__forceinline Type getType() const { return type; }
		__forceinline maths::vec3 getPosition() { return position; }

	protected:
		maths::mat4 generateModelMatrix() const;

	public:
		bool operator==(Entity &other) const;
	};
} }
