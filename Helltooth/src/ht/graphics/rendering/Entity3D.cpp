#include "Entity3D.h"

namespace ht { namespace graphics {


	Entity3D::Entity3D(const float &x, const float &y, const float &z) {
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
		m_Scale = vec3(1, 1, 1);
		modelMatrix = generateModelMatrix();
	}

	Entity3D::Entity3D() {
		m_Position.x = 0;
		m_Position.y = 0;
		m_Position.z = 0;
		m_Scale = vec3(1, 1, 1);
		modelMatrix = generateModelMatrix();
	}

	Entity3D::Entity3D(const vec3 position) {
		m_Position = position;
		modelMatrix = generateModelMatrix();
	}

	void Entity3D::move(vec3 &move) {
		m_Position = m_Position + move;
		modelMatrix = generateModelMatrix();
	}

	//Rotate the entity 
	//Eg: rotate(vec3(90,0,0)) -> rotates 90 degrees on the x axis
	void Entity3D::rotate(vec3 &axis) {
		m_Rotation.x += axis.x;
		m_Rotation.y += axis.y;
		m_Rotation.z += axis.z;
		modelMatrix = generateModelMatrix();
	}

	//Scale the entity: make it bigger or smaller
	//Eg: scale(3,3,3) -> makes the model 3 times bigger
	void Entity3D::scale(const float &scaleX, const float &scaleY, const float &scaleZ) {
		m_Scale.x += scaleX;
		m_Scale.y += scaleY;
		m_Scale.z += scaleZ;
		modelMatrix = generateModelMatrix();
	}

	//Scale the entity: make it bigger or smaller
	//Eg: scale(vec3(3,3,3)) -> makes the model 3 times bigger
	void Entity3D::scale(const vec3 scale) {
		m_Scale = scale;
		modelMatrix = generateModelMatrix();
	}

	//Generate the model matrix of the entity
	//Used for shader
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
	
	mat4 Entity3D::generateRotateMatrix() const {
		mat4 rotate = mat4::createIdentity();
		rotate.rotate(m_Rotation);
		return rotate;
	}

	mat4 Entity3D::generateTranslationMatrix() const {
		mat4 result = mat4::createIdentity();
		result.translate(m_Position);
		return result;
	}

	mat4 Entity3D::generateScaleMatrix() const {
		mat4 move = mat4::createIdentity();
		move.scale(m_Scale);
		return move;
	}

	//Operator used for testing if two entities are the same
	bool Entity3D::operator==(Entity3D &other) const {
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