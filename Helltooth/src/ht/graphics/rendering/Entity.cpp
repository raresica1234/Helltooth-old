#include "Entity.h"

namespace ht { namespace graphics {
	using namespace maths;

	Entity::Entity(const float &x, const float &y, const float &z) {
		m_Position.x = x;
		m_Position.y = y;
		m_Position.z = z;
		m_Scale = vec3(1, 1, 1);
		modelMatrix = generateModelMatrix();
	}

	Entity::Entity() {
		m_Position.x = 0;
		m_Position.y = 0;
		m_Position.z = 0;
		m_Scale = vec3(1, 1, 1);
		modelMatrix = generateModelMatrix();
	}

	Entity::Entity(const vec3 position) {
		m_Position = position;
		modelMatrix = generateModelMatrix();
	}

	void Entity::move(vec3 &move) {
		m_Position = m_Position + move;
		modelMatrix = generateModelMatrix();
	}

	//Rotate the entity 
	//Eg: rotate(vec3(90,0,0)) -> rotates 90 degrees on the x axis
	void Entity::rotate(vec3 &axis) {
		m_Rotation.x += axis.x;
		m_Rotation.y += axis.y;
		m_Rotation.z += axis.z;
		modelMatrix = generateModelMatrix();
	}

	//Scale the entity: make it bigger or smaller
	//Eg: scale(3,3,3) -> makes the model 3 times bigger
	void Entity::scale(const float &scaleX, const float &scaleY, const float &scaleZ) {
		m_Scale.x += scaleX;
		m_Scale.y += scaleY;
		m_Scale.z += scaleZ;
		modelMatrix = generateModelMatrix();
	}

	//Scale the entity: make it bigger or smaller
	//Eg: scale(vec3(3,3,3)) -> makes the model 3 times bigger
	void Entity::scale(const vec3 scale) {
		m_Scale = scale;
		modelMatrix = generateModelMatrix();
	}

	//Generate the model matrix of the entity
	//Used for shader
	mat4 Entity::generateModelMatrix() const {
		mat4 result = mat4().translate(m_Position).rotate(m_Rotation).scale(m_Scale);
		return result;
	}

	//Operator used for testing if two entities are the same
	bool Entity::operator==(Entity &other) const {
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