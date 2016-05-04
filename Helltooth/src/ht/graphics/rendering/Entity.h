#pragma once

#include "../../maths/vec3.h"
#include "../../maths/mat4.h"



namespace ht { namespace graphics {

	using namespace maths;

	class Entity {
#if API_MODE == API_MODE_3D
	private:
		vec3 m_Position;
		vec3 m_Rotation;
		vec3 m_Scale;

	public:
		Entity(const float &x, const float &y, const float &z) {
			m_Position.x = x;
			m_Position.y = y;
			m_Position.z = z;
		}

		Entity(const vec3 position) {
			m_Position = position;
		}

		void rotate(const float &angle, vec3 axis);

		void scale(const float &scaleX, const float &scaleY, const float &scaleZ);
		void scale(const vec3 scale);

		mat4 generateModelMatrix() const;

#else
	private:
		vec3 position;
		float rotation;
		vec3 scale;

	public:
		Entity(const float &x, const float &y, const float &z) {
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
		}

		Entity(const vec3 position) {
			this->position = position;
		}

		void rotate(const float &angle);

		void scale(const float &scaleX, const float &scaleY, const float &scaleZ);
		void scale(const vec3 scale);

		mat4 generateModelMatrix() const;

#endif
	};

} }
