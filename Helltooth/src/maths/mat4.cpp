#include "mat4.h"

namespace ht { namespace maths {

	mat4::mat4() {
		for (int i = 0; i < (sizeof(elements) / sizeof(float)); i++) {
			elements[i] = 0;
		}
	}

	mat4 mat4::createProjection(const int &FOV, const int &NEAR_PLANE, const int &FAR_PLANE, const int &WIDTH, const int &HEIGHT) {
		float aspectRatio = WIDTH / HEIGHT;
		float halftan = tanh(FOV * (float)(3.14159265358979323846 / 180.f));
		float zm = FAR_PLANE - NEAR_PLANE;
		float zp = FAR_PLANE + NEAR_PLANE;

		mat4 result = mat4();
		
		result.elements[0 + 0 * 4] = (1.0f / halftan) / aspectRatio;
		result.elements[1 + 1 * 4] = (1.0f / halftan);
		result.elements[2 + 2 * 4] = -zp / zm;
		result.elements[3 + 2 * 4] = -(2 * FAR_PLANE*NEAR_PLANE) / zm;
		result.elements[2 + 3 * 4] = -1;

		return result;
	}

	mat4 mat4::createOrthographic(const int &left, const int &right, const int &top, const int &bottom, const int &far, const int &near) {
		mat4 result = createIdentity();

		result.elements[0 + 0 * 4] = 2 / (right - left);
		result.elements[1 + 1 * 4] = 2 / (top - bottom);
		result.elements[2 + 2 * 4] = -2 / (far - near);

		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}

	mat4 mat4::createIdentity() {
		//TODO: Suspicious looking memory leak.
		mat4 result = mat4();
		result.elements[0 + 0 * 4] = 1;
		result.elements[1 + 1 * 4] = 1;
		result.elements[2 + 2 * 4] = 1;
		result.elements[3 + 3 * 4] = 1;
		return result;
	}


	void mat4::translate(const vec3 &translation) {
		elements[3 + 0 * 4] = translation.x;
		elements[3 + 1 * 4] = translation.y;
		elements[3 + 2 * 4] = translation.z;
	}

	void mat4::scale(const vec3 &scale) {
		elements[0 + 0 * 4] = scale.x;
		elements[1 + 1 * 4] = scale.y;
		elements[2 + 2 * 4] = scale.z;
	}

	void mat4::rotate(const float &angle, const vec3 &axis) {
		double s = sin(angle * (float)(3.14159265358979323846 / 180.f));
		double c = cos(angle * (float)(3.14159265358979323846 / 180.f));
		
		mat4 identity = mat4::createIdentity();

		for (int i = 0; i < sizeof(elements) / sizeof(float); i++)
			this->elements[i] = identity.elements[i];

		if (axis.x > 0) {
			elements[1 + 1 * 4] = c;
			elements[2 + 1 * 4] = -s;
			elements[1 + 2 * 4] = s;
			elements[2 + 2 * 4] = c;
		}
		else if (axis.y > 0) {
			elements[0 + 0 * 4] = c;
			elements[2 + 0 * 4] = s;
			elements[0 + 2 * 4] = -s;
			elements[2 + 2 * 4] = c;
		}
		else if (axis.z > 0) {
			elements[0 + 0 * 4] = c;
			elements[1 + 0 * 4] = -s;
			elements[0 + 1 * 4] = s;
			elements[1 + 1 * 4] = c;
		}
		delete &identity;
	}

} }