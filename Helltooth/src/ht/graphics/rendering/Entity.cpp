#include "Entity.h"

namespace ht { namespace graphics {

#if API_MODE == API_MODE_3D

	void Entity::rotate(const float &angle, vec3 axis) {
		if (axis.x == 1)
			m_Rotation.x += angle;
		if (axis.y == 1)
			m_Rotation.y += angle;
		if (axis.z == 1)
			m_Rotation.z += angle;
	}

	void Entity::scale(const float &scaleX, const float &scaleY, const float &scaleZ) {
		m_Scale.x += scaleX;
		m_Scale.y += scaleY;
		m_Scale.z += scaleZ;
	}

	void Entity::scale(const vec3 scale) {
		m_Scale = scale;
	}


	mat4 Entity::generateModelMatrix() const {
		mat4 result = mat4::createIdentity();
		result.scale(m_Scale);
		mat4 rotate = mat4::createIdentity();
		
		rotate.rotate(m_Rotation);

		mat4 move = mat4::createIdentity();
		move.translate(m_Position);
		result = result * move;
		return result;
	}

#else

#endif


} }