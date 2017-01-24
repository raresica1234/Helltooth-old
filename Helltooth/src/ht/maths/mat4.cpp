#include "mat4.h"

namespace ht { namespace maths {

	mat4::mat4() {
		memset(&elements, 0, sizeof(elements));
	}

	mat4 mat4::createPerspective(const float &FOV, const float &NEAR_PLANE, const float &FAR_PLANE, const float &ASPECT_RATIO) {

		mat4 result;

		float tanHalf = tanh(FOV / 2.0f);

		result.elements[0 + 0 * 4] = 1.0f / (tanHalf * ASPECT_RATIO);
		result.elements[1 + 1 * 4] = 1.0f / tanHalf;
		result.elements[2 + 2 * 4] = -(FAR_PLANE + NEAR_PLANE) / (FAR_PLANE - NEAR_PLANE);
		result.elements[3 + 2 * 4] = -1.0f;
		result.elements[2 + 3 * 4] = -(2.0f * FAR_PLANE * NEAR_PLANE) / (FAR_PLANE - NEAR_PLANE);
		result.elements[3 + 3 * 4] = 0.0f;

		return result;
	}

	mat4 mat4::createOrthographic(const float &left, const float &right, const float &top, const float &bottom, const float &near, const float &far) {
		mat4 result = createIdentity();

		result.elements[0 + 0 * 4] = 2.0f / (right - left);
		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		result.elements[2 + 2 * 4] = -2.0f / (far - near);

		result.elements[0 + 3 * 4] = -((right + left) / (right - left));
		result.elements[1 + 3 * 4] = -((top + bottom) / (top - bottom));
		result.elements[2 + 3 * 4] = -((far + near) / (near - far));

		result.elements[3 + 3 * 4] = 1;

		return result;
	}

	mat4 mat4::createIdentity() {
		mat4 result = mat4();
		result.elements[0 + 0 * 4] = 1;
		result.elements[1 + 1 * 4] = 1;
		result.elements[2 + 2 * 4] = 1;
		result.elements[3 + 3 * 4] = 1;
		return result;
	}


	void mat4::translate(const vec3 &translation) {
		elements[0 + 3 * 4] = translation.x;
		elements[1 + 3 * 4] = translation.y;
		elements[2 + 3 * 4] = translation.z;
	}

	void mat4::scale(const vec3 &scale) {
		elements[0 + 0 * 4] = scale.x;
		elements[1 + 1 * 4] = scale.y;
		elements[2 + 2 * 4] = scale.z;
	}

	void mat4::rotate(const vec3 &axis) {
		mat4 x = mat4::createIdentity();
		mat4 y = mat4::createIdentity();
		mat4 z = mat4::createIdentity();

		float xcos = cosf((float)toRadians(axis.x));
		float xsin = sinf((float)toRadians(axis.x));
		float ycos = cosf((float)toRadians(axis.y));
		float ysin = sinf((float)toRadians(axis.y));
		float zcos = cosf((float)toRadians(axis.z));
		float zsin = sinf((float)toRadians(axis.z));

		x.elements[1 + 1 * 4] = xcos;
		x.elements[1 + 2 * 4] = -xsin;
		x.elements[2 + 1 * 4] = xsin;
		x.elements[2 + 2 * 4] = xcos;

		y.elements[0 + 0 * 4] = ycos;
		y.elements[0 + 2 * 4] = -ysin;
		y.elements[2 + 0 * 4] = ysin;
		y.elements[2 + 2 * 4] = ycos;

		z.elements[0 + 0 * 4] = zcos;
		z.elements[0 + 1 * 4] = -zsin;
		z.elements[1 + 0 * 4] = zsin;
		z.elements[1 + 1 * 4] = zcos;

		*this = (x * y * z);
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
			left.columns[0].z * right.x + left.columns[1].z * right.y + left.columns[3].z * right.z + left.columns[3].z);
	}

	vec2 operator*(mat4 left, const vec2 &right) {
		return vec2(
			left.columns[0].x * right.x + left.columns[1].x * right.y + left.columns[2].x + left.columns[3].x,
			left.columns[0].y * right.x + left.columns[1].y * right.y + left.columns[2].y + left.columns[3].y);
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