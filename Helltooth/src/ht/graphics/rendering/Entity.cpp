#include "Entity.h"

namespace ht { namespace graphics {
	using namespace maths;

	Entity::Entity(const f32 &x, const f32 &y, const f32 &z)
		: position(x,y,z), vscale(1, 1, 1) {
		modelMatrix = generateModelMatrix();
	}

	Entity::Entity()
		: position(), vscale(1, 1, 1) {
		modelMatrix = generateModelMatrix();
	}

	Entity::Entity(const vec3 position) {
		this->position = position;
		modelMatrix = generateModelMatrix();
	}

	void Entity::move(vec3 &move) {
		position = position + move;
		modelMatrix = generateModelMatrix();
	}

	//Rotate the entity 
	//Eg: rotate(vec3(90,0,0)) -> rotates 90 degrees on the x axis
	void Entity::rotate(vec3 &axis) {
		rotation.x += axis.x;
		rotation.y += axis.y;
		rotation.z += axis.z;
		modelMatrix = generateModelMatrix();
	}

	//Scale the entity: make it bigger or smaller
	//Eg: scale(3,3,3) -> makes the model 3 times bigger
	void Entity::scale(const f32 &scaleX, const f32 &scaleY, const f32 &scaleZ) {
		vscale.x += scaleX;
		vscale.y += scaleY;
		vscale.z += scaleZ;
		modelMatrix = generateModelMatrix();
	}

	//Scale the entity: make it bigger or smaller
	//Eg: scale(vec3(3,3,3)) -> makes the model 3 times bigger
	void Entity::scale(const vec3 scale) {
		vscale = scale;
		modelMatrix = generateModelMatrix();
	}

	//Generate the model matrix of the entity
	//Used for shader
	mat4 Entity::generateModelMatrix() const {
		mat4 result = mat4().translate(position).rotate(rotation).scale(vscale);
		return result;
	}

	//Operator used for testing if two entities are the same
	bool Entity::operator==(Entity &other) const {
		if (position == other.position) {
			if (rotation == other.rotation) {
				if (vscale == other.vscale) {
					return true;
				}
			}
		}
		return false;
	}
} }