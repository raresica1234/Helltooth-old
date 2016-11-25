#pragma once

#include "../../maths/vec3.h"
#include "../../maths/mat4.h"
#include "Renderable.h"


namespace ht { namespace graphics {

	class Entity3D {
	protected:
		//Entity data
		ht::maths::vec3 m_Position;
		ht::maths::vec3 m_Rotation;
		ht::maths::vec3 m_Scale;
		mutable ht::maths::mat4 modelMatrix;

	public:

		//Constructor
		//Entity(positionX, positionY, positionZ)
		Entity3D(const float &x, const float &y, const float &z);

		//Default constructor
		//Sets everything to 0 (default) and the scale to 1
		Entity3D();

		Entity3D(const ht::maths::vec3 position);

		void rotate(ht::maths::vec3 &axis);

		void scale(const float &scaleX, const float &scaleY, const float &scaleZ);
		void scale(const ht::maths::vec3 scale);

		inline ht::maths::mat4 getModelMatrix() const { return modelMatrix; }

		void move(ht::maths::vec3 &move);

	protected:
		ht::maths::mat4 generateModelMatrix() const;
		ht::maths::mat4 generateRotateMatrix() const;
		ht::maths::mat4 generateTranslationMatrix() const;
		ht::maths::mat4 generateScaleMatrix() const;

	public:
		bool operator==(Entity3D &other) const;

	};

} }
