#include "Entity3D.h"

namespace ht { namespace graphics {

	void Entity3D::rotate(const float &angle, vec3 axis) {
		if (axis.x == 1)
			m_Rotation.x += angle;
		if (axis.y == 1)
			m_Rotation.y += angle;
		if (axis.z == 1)
			m_Rotation.z += angle;
	}

	void Entity3D::scale(const float &scaleX, const float &scaleY, const float &scaleZ) {
		m_Scale.x += scaleX;
		m_Scale.y += scaleY;
		m_Scale.z += scaleZ;
	}

	void Entity3D::scale(const vec3 scale) {
		m_Scale = scale;
	}


	mat4 Entity3D::generateModelMatrix() const {
		mat4 result = mat4::createIdentity();
		result.scale(m_Scale);
		mat4 rotate = mat4::createIdentity();

		rotate.rotate(m_Rotation);

		mat4 move = mat4::createIdentity();
		move.translate(m_Position);
		result = result * move;
		return result;
	}

} }