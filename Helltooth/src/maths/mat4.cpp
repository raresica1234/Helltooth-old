#include "mat4.h"

namespace ht { namespace maths {

	mat4::mat4() {
		memset(elements, 0, sizeof(elements));
	}

	mat4 mat4::createProjection(const float &FOV, const float &NEAR_PLANE, const float &FAR_PLANE, const int &WIDTH, const int &HEIGHT) {
		mat4 result = mat4();
		float aspectRatio = WIDTH / HEIGHT;
		float tanHalf = tanh(FOV / 2);

		result.elements[0 + 0 * 4] = 1.0f / (tanHalf * aspectRatio);
		result.elements[1 + 1 * 4] = 1.0f / tanHalf;
		result.elements[2 + 2 * 4] = -(FAR_PLANE + NEAR_PLANE) / (FAR_PLANE - NEAR_PLANE);
		result.elements[3 + 2 * 4] = -1;
		result.elements[2 + 3 * 4] = -(2 * FAR_PLANE * NEAR_PLANE) / (FAR_PLANE - NEAR_PLANE);
		result.elements[3 + 3 * 4] = 0;



		return result;
	}

	mat4 mat4::createOrthographic(const float &left, const float &right, const float &top, const float &bottom, const float &far, const float &near) {
		mat4 result = createIdentity();

		result.elements[0 + 0 * 4] = (float) 2 / (right - left);
		result.elements[1 + 1 * 4] = (float) 2 / (top - bottom);
		result.elements[2 + 2 * 4] = (float) -2 / (far - near);

		result.elements[0 + 3 * 4] = (float) (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (float) (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (float) (far + near) / (far - near);

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
		float s = (float) sin(angle * (float)(3.14159265358979323846 / 180.f));
		float c = (float) cos(angle * (float)(3.14159265358979323846 / 180.f));
		
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

	mat4 operator*(mat4 left, const mat4 &right) {
		float data[4 * 4];
		for (int x = 0; x < 4; x++) {
			for (int y = 0; y < 4; y++) {
				float sum = 0.0f;
				for (int e = 0; e < 4; e++) {
					sum += left.elements[x + e * 4] * right.elements[e + y * 4];
					data[x + y * 4] = sum;
				}
			}
		}

		for (int i = 0; i < (sizeof(left.elements) / sizeof(float)); i++) {
			left.elements[i] = data[i];
		}
		
		return left;
	}

	vec4 operator*(mat4 left, const vec4 &right) {
		return vec4(
			left.columns[0].x * right.x + left.columns[1].x * right.y + left.columns[2].x * right.z + left.columns[3].x * right.w,
			left.columns[0].y * right.x + left.columns[1].y * right.y + left.columns[2].y * right.z + left.columns[3].y * right.w,
			left.columns[0].z * right.x + left.columns[1].z * right.y + left.columns[2].z * right.z + left.columns[3].z * right.w,
			left.columns[0].w * right.x + left.columns[1].w * right.y + left.columns[2].w * right.z + left.columns[3].w * right.w);
	}

	vec3 operator*(mat4 left, const vec3 &right) {
		return vec3(
			left.columns[0].x * right.x + left.columns[1].x * right.y + left.columns[2].x * right.z + left.columns[3].x,
			left.columns[0].y * right.x + left.columns[1].y * right.y + left.columns[2].y * right.z + left.columns[3].y,
			left.columns[0].z * right.x + left.columns[1].z * right.y + left.columns[3].z * right.z + left.columns[3].z
			);
	}

	vec2 operator*(mat4 left, const vec2 &right) {
		return vec2(
			left.columns[0].x * right.x + left.columns[1].x * right.y + left.columns[2].x + left.columns[3].x,
			left.columns[0].y * right.x + left.columns[1].y * right.y + left.columns[2].y + left.columns[3].y
			);
	}

	mat4 mat4::operator*=(const mat4& other) {
		return (*this) * other;
	}

	vec4 mat4::operator*=(const vec4 &other) {
		return (*this) * other;
	}

	vec3 mat4::operator*=(const vec3 &other) {
		return (*this) * other;
	}

	vec2 mat4::operator*=(const vec2 &other) {
		return (*this) * other;
	}

} }