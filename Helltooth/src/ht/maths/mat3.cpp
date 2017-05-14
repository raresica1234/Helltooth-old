#include "mat3.h"

namespace ht { namespace maths {
#define set_ps _mm_set_ps

	void mat3::loadRows(m128* xmm) const {
		xmm[0] = set_ps(elements[0 + 3 * 3], elements[0 + 2 * 3], elements[0 + 1 * 3], elements[0 + 0 * 3]);
		xmm[1] = set_ps(elements[1 + 3 * 3], elements[1 + 2 * 3], elements[1 + 1 * 3], elements[1 + 0 * 3]);
		xmm[2] = set_ps(elements[2 + 3 * 3], elements[2 + 2 * 3], elements[2 + 1 * 3], elements[2 + 0 * 3]);
	}

	void mat3::loadColumns(m128* xmm) const {
		xmm[0] = set_ps(elements[3 + 0 * 3], elements[2 + 0 * 3], elements[1 + 0 * 3], elements[0 + 0 * 3]);
		xmm[1] = set_ps(elements[3 + 1 * 3], elements[2 + 1 * 3], elements[1 + 1 * 3], elements[0 + 1 * 3]);
		xmm[2] = set_ps(elements[3 + 2 * 3], elements[2 + 2 * 3], elements[1 + 2 * 3], elements[0 + 2 * 3]);
	}

	mat3::mat3() {
		memset(&elements, 0, sizeof(elements));
		elements[0 + 0 * 3] = 1.f;
		elements[1 + 1 * 3] = 1.f;
		elements[2 + 2 * 3] = 1.f;
	}

	mat3& mat3::scale(const f32 &x, const f32 &y) {
		mat3 add;
		add[0 + 2 * 3] = x;
		add[1 + 2 * 3] = y;
		*this *= add;
		return *this;
	}

	mat3& mat3::scale(const vec2 &scale) {
		return this->scale(scale.x, scale.y);
	}

	mat3& mat3::rotate(const f32& z) {
		mat3 add;
		f32 angle = toRadians(z);
		add[0 + 0 * 3] = cos(angle); add[0 + 1 * 3] = -sin(angle);// 0
		add[1 + 0 * 3] = sin(angle); add[1 + 1 * 3] = cos(angle); // 0
		//0                          0                               1
		*this *= add;
		return *this;
	}

	mat3 operator*(mat3 left, const mat3 &right) {
		mat3 tmp;

		mat3::m128 col[3];
		mat3::m128 row[3];

		right.loadColumns(col);
		left.loadRows(row);

		for (int y = 0; y < 3; y++)
			for (int x = 0; x < 3; x++) {
				mat3::m128 res = _mm_mul_ps(row[x], col[y]);
				tmp[x + y * 3] = res.m128_f32[0] + res.m128_f32[1] + res.m128_f32[2];
			}

		return tmp;
	}

	vec3 operator*(mat3 left, const vec3 &right) {
		__m128 vec[3];
		__m128 col[3];

		vec[0] = _mm_set_ps(right.x, right.x, right.x, right.x);
		vec[1] = _mm_set_ps(right.y, right.y, right.y, right.y);
		vec[2] = _mm_set_ps(right.z, right.z, right.z, right.z);

		left.loadColumns(col);

		__m128 res = _mm_mul_ps(vec[0], col[0]);

		for (int32 i = 1; i < 3; i++)
			res = _mm_fmadd_ps(vec[i], col[i], res);

		return vec3(res.m128_f32[0], res.m128_f32[1], res.m128_f32[2]);
	}

	vec2 operator*(mat3 left, const vec2 &right) {
		__m128 vec[3];
		__m128 col[3];

		vec[0] = _mm_set_ps(right.x, right.x, right.x, right.x);
		vec[1] = _mm_set_ps(right.y, right.y, right.y, right.y);
		vec[2] = _mm_set_ps(1, 1, 1, 1);

		__m128 res = _mm_mul_ps(vec[0], col[0]);

		for (int i = 1; i < 3; i++)
			res = _mm_fmadd_ps(vec[i], col[i], res);

		return vec2(res.m128_f32[0], res.m128_f32[1]);
	}

	mat3 mat3::operator*=(const mat3 &other) {
		return (*this) * other;
	}

	vec3 mat3::operator*=(const vec3 &other) {
		return (*this) * other;
	}

	vec2 mat3::operator*=(const vec2 &other) {
		return (*this) * other;
	}

	float& mat3::operator[](unsigned int index) {
		return elements[index];
	}

} }
