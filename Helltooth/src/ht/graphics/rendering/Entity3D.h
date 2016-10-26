#pragma once

#include "../../maths/vec3.h"
#include "../../maths/mat4.h"
#include "Renderable.h"


namespace ht { namespace graphics {

	using namespace maths;

	class Entity3D {
	protected:
		//Entity data
		vec3 m_Position;
		vec3 m_Rotation;
		vec3 m_Scale;
		mutable mat4 modelMatrix;


	public:

		//Constructor
		//Entity(positionX, positionY, positionZ)
		Entity3D(const float &x, const float &y, const float &z);

		//Default constructor
		//Sets everything to 0 (default) and the scale to 1
		Entity3D();

		Entity3D(const vec3 position);

		void rotate(vec3 &axis);

		void scale(const float &scaleX, const float &scaleY, const float &scaleZ);
		void scale(const vec3 scale);

		inline mat4 getModelMatrix() const { return modelMatrix; }

		void move(vec3 &move);

	protected:
		mat4 generateModelMatrix() const;
		mat4 generateRotateMatrix() const;
		mat4 generateTranslationMatrix() const;
		mat4 generateScaleMatrix() const;

	public:
		bool operator==(Entity3D &other);

	};

} }
