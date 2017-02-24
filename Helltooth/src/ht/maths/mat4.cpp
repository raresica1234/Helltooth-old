#include "mat4.h"

namespace ht { namespace maths {
#define set_ps _mm_set_ps

	void mat4::loadRows(m128* xmm) const {
		xmm[0] = set_ps(elements[0 + 3 * 4], elements[0 + 2 * 4], elements[0 + 1 * 4], elements[0 + 0 * 4]);
		xmm[1] = set_ps(elements[1 + 3 * 4], elements[1 + 2 * 4], elements[1 + 1 * 4], elements[1 + 0 * 4]);
		xmm[2] = set_ps(elements[2 + 3 * 4], elements[2 + 2 * 4], elements[2 + 1 * 4], elements[2 + 0 * 4]);
		xmm[3] = set_ps(elements[3 + 3 * 4], elements[3 + 2 * 4], elements[3 + 1 * 4], elements[3 + 0 * 4]);
	}

	void mat4::loadColumns(m128* xmm) const {
		xmm[0] = set_ps(elements[3 + 0 * 4], elements[2 + 0 * 4], elements[1 + 0 * 4], elements[0 + 0 * 4]);
		xmm[1] = set_ps(elements[3 + 1 * 4], elements[2 + 1 * 4], elements[1 + 1 * 4], elements[0 + 1 * 4]);
		xmm[2] = set_ps(elements[3 + 2 * 4], elements[2 + 2 * 4], elements[1 + 2 * 4], elements[0 + 2 * 4]);
		xmm[3] = set_ps(elements[3 + 3 * 4], elements[2 + 3 * 4], elements[1 + 3 * 4], elements[0 + 3 * 4]);
	}

	mat4::mat4() {
		memset(&elements, 0, sizeof(elements));
		elements[0 + 0 * 4] = 1.f;
		elements[1 + 1 * 4] = 1.f;
		elements[2 + 2 * 4] = 1.f;
		elements[3 + 3 * 4] = 1.f;
	}

	mat4 mat4::createPerspective(const float &FOV, const float &NEAR_PLANE, const float &FAR_PLANE, const float &ASPECT_RATIO) {

		mat4 result = mat4();

		float tanHalf = tanh(toRadians(FOV) / 2.0f);

		result.elements[0 + 0 * 4] = 1.0f / (tanHalf * ASPECT_RATIO);
		result.elements[1 + 1 * 4] = 1.0f / tanHalf;
		result.elements[2 + 2 * 4] = -(FAR_PLANE + NEAR_PLANE) / (FAR_PLANE - NEAR_PLANE);
		result.elements[3 + 2 * 4] = -1.0f;
		result.elements[2 + 3 * 4] = -(2.0f * FAR_PLANE * NEAR_PLANE) / (FAR_PLANE - NEAR_PLANE);
		result.elements[3 + 3 * 4] = 0.0f;

		return result;
	}

	mat4 mat4::createOrthographic(const float &left, const float &right, const float &top, const float &bottom, const float &near, const float &far) {
		mat4 result = mat4();

		result.elements[0 + 0 * 4] = 2.0f / (right - left);
		result.elements[1 + 1 * 4] = 2.0f / (top - bottom);
		result.elements[2 + 2 * 4] = 2.0f / (near - far);

		result.elements[0 + 3 * 4] = (left + right) / (left - right);
		result.elements[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result.elements[2 + 3 * 4] = (far + near) / (far - near);

		return result;
	}


	mat4& mat4::translate(const float &x, const float &y, const float &z) {
		mat4 add = mat4();
		add[0 + 3 * 4] = x;
		add[1 + 3 * 4] = y;
		add[2 + 3 * 4] = z;
		*this = *this * add;
		return *this;
	}

	mat4& mat4::translate(const vec3 &translation) {
		return translate(translation.x, translation.y, translation.z);
	}


	mat4& mat4::scale(const float &x, const float &y, const float &z) {
		mat4 add = mat4();
		add[0 + 0 * 4] = x;
		add[1 + 1 * 4] = y;
		add[2 + 2 * 4] = z;
		*this = *this * add;
		return *this;
	}

	mat4& mat4::scale(const vec3 &scale) {
		return this->scale(scale.x, scale.y, scale.z);
	}


	mat4& mat4::rotate(const float &x, const float &y, const float &z) {
		mat4 rotx = mat4();
		mat4 roty = mat4();
		mat4 rotz = mat4();

		float xcos = cosf((float)toRadians(x));
		float xsin = sinf((float)toRadians(x));
		float ycos = cosf((float)toRadians(y));
		float ysin = sinf((float)toRadians(y));
		float zcos = cosf((float)toRadians(z));
		float zsin = sinf((float)toRadians(z));

		rotx[1 + 1 * 4] = xcos;
		rotx[1 + 2 * 4] = -xsin;
		rotx[2 + 1 * 4] = xsin;
		rotx[2 + 2 * 4] = xcos;

		roty[0 + 0 * 4] = ycos;
		roty[0 + 2 * 4] = -ysin;
		roty[2 + 0 * 4] = ysin;
		roty[2 + 2 * 4] = ycos;

		rotz[0 + 0 * 4] = zcos;
		rotz[0 + 1 * 4] = -zsin;
		rotz[1 + 0 * 4] = zsin;
		rotz[1 + 1 * 4] = zcos;

		mat4 result = mat4();
		result = rotx * roty * rotz;
		*this = *this * result;
		return *this;
	}

	mat4& mat4::rotate(const vec3 &axis) {
		return rotate(axis.x, axis.y, axis.z);
	}

	mat4 operator*(mat4 left, const mat4 &right) {
		mat4 tmp;
		mat4::m128 col[4];
		mat4::m128 rows[4];

		right.loadColumns(col);
		left.loadRows(rows);

		for (int y = 0; y < 4; y++) {
			for (int x = 0; x < 4; x++) {
				mat4::m128 res = _mm_mul_ps(rows[x], col[y]);
				tmp[x + y * 4] = res.m128_f32[0] + res.m128_f32[1] + res.m128_f32[2] + res.m128_f32[3];
			}
		}

		return tmp;
	}

	vec4 operator*(mat4 left, const vec4 &right) {
		__m128 vec[4];
		__m128 col[4];

		vec[0] = _mm_set_ps(right.x, right.x, right.x, right.x);
		vec[1] = _mm_set_ps(right.y, right.y, right.y, right.y);
		vec[2] = _mm_set_ps(right.z, right.z, right.z, right.z);
		vec[3] = _mm_set_ps(right.w, right.w, right.w, right.w);

		left.loadColumns(col);

		__m128 res = _mm_mul_ps(vec[0], col[0]);

		for (int i = 1; i < 4; i++)
			res = _mm_fmadd_ps(vec[i], col[i], res);

		return vec4(res.m128_f32[0], res.m128_f32[1], res.m128_f32[2], res.m128_f32[3]);
	}

	vec3 operator*(mat4 left, const vec3 &right) {
		__m128 vec[4];
		__m128 col[4];

		vec[0] = _mm_set_ps(right.x, right.x, right.x, right.x);
		vec[1] = _mm_set_ps(right.y, right.y, right.y, right.y);
		vec[2] = _mm_set_ps(right.z, right.z, right.z, right.z);
		vec[3] = _mm_set_ps(1, 1, 1, 1);

		left.loadColumns(col);

		__m128 res = _mm_mul_ps(vec[0], col[0]);

		for (int i = 1; i < 4; i++)
			res = _mm_fmadd_ps(vec[i], col[i], res);

		return vec3(res.m128_f32[0], res.m128_f32[1], res.m128_f32[2]);
	}

	vec2 operator*(mat4 left, const vec2 &right) {
		__m128 vec[4];
		__m128 col[4];
		
		vec[0] = _mm_set_ps(right.x, right.x, right.x, right.x);
		vec[1] = _mm_set_ps(right.y, right.y, right.y, right.y);
		vec[2] = _mm_set_ps(1, 1, 1, 1);
		vec[3] = _mm_set_ps(1, 1, 1, 1);

		__m128 res = _mm_mul_ps(vec[0], col[0]);

		for (int i = 1; i < 4; i++)
			res = _mm_fmadd_ps(vec[i], col[i], res);

		return vec2(res.m128_f32[0], res.m128_f32[1]);
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

	float& mat4::operator[](unsigned int index) {
		return elements[index];
	}

} }