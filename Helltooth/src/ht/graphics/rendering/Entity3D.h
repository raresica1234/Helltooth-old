#pragma once

#include "../../maths/vec3.h"
#include "../../maths/mat4.h"
#include "Renderable.h"


namespace ht { namespace graphics {

	using namespace maths;

	class Entity3D {
	private:
		//Entity data
		vec3 m_Position;
		vec3 m_Rotation;
		vec3 m_Scale;

	public:

		//Constructor
		//Entity(positionX, positionY, positionZ)
		Entity3D(const float &x, const float &y, const float &z) {
			m_Position.x = x;
			m_Position.y = y;
			m_Position.z = z;
			m_Scale = vec3(1, 1, 1);
		}

		//Default constructor
		//Sets everything to 0 (default) and the scale to 1
		Entity3D() {
			m_Position.x = 0;
			m_Position.y = 0;
			m_Position.z = 0;
			m_Scale = vec3(1, 1, 1);
		}

		Entity3D(const vec3 position) {
			m_Position = position;
		}

		void rotate(vec3 &axis);

		void scale(const float &scaleX, const float &scaleY, const float &scaleZ);
		void scale(const vec3 scale);

		mat4 generateModelMatrix() const;

	protected:
		inline mat4 generateRotateMatrix() const {
			mat4 rotate = mat4::createIdentity();
			rotate.rotate(m_Rotation);
			return rotate;
		}

		inline mat4 generateTranslationMatrix() const {
			mat4 result = mat4::createIdentity();
			result.translate(m_Position);
			return result;
		}

		inline mat4 generateScaleMatrix() const {
			mat4 move = mat4::createIdentity();
			move.scale(m_Scale);
			return move;
		}

	public:
		bool operator==(Entity3D &other);

	};

} }
