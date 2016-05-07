#pragma once

#include "../../maths/vec3.h"
#include "../../maths/mat4.h"
#include "Renderable.h"


namespace ht { namespace graphics {

	using namespace maths;

	class Entity3D {
	private:
		vec3 m_Position;
		vec3 m_Rotation;
		vec3 m_Scale;

	public:
		Entity3D(const float &x, const float &y, const float &z) {
			m_Position.x = x;
			m_Position.y = y;
			m_Position.z = z;
		}

		Entity3D(const vec3 position) {
			m_Position = position;
		}

		void rotate(const float &angle, vec3 axis);

		void scale(const float &scaleX, const float &scaleY, const float &scaleZ);
		void scale(const vec3 scale);

		mat4 generateModelMatrix() const;


		void render() const;
	};

} }
