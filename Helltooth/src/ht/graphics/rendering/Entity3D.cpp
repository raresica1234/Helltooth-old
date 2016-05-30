#include "Entity3D.h"

namespace ht { namespace graphics {

	void Entity3D::rotate(vec3 &axis) {
		m_Rotation.x += axis.x;
		m_Rotation.y += axis.y;
		m_Rotation.z += axis.z;
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
		result.translate(m_Position);

		mat4 rotate = mat4::createIdentity();
		rotate.rotate(m_Rotation);

		result = result * rotate;

		mat4 move = mat4::createIdentity();
		move.scale(m_Scale);

		result = result * move;

		return result;
	}

	bool Entity3D::operator==(Entity3D &other) {
		if (m_Position.x == other.m_Position.x && m_Position.y == other.m_Position.y && m_Position.z == other.m_Position.z) {
			if (m_Rotation.x == other.m_Rotation.x && m_Rotation.y == other.m_Rotation.y && m_Rotation.z == other.m_Rotation.z) {
				if (m_Scale.x == m_Scale.x && m_Scale.y == m_Scale.y && m_Scale.z == m_Scale.z) {
					return true;
				}
			}
		}
		return false;
	}

} }