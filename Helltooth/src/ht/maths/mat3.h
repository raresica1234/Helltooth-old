#pragma once

#include "vec2.h"
#include "vec3.h"
#include "maths.h"

#include "utils/Internal.h"

namespace ht { namespace maths {

	struct mat3 {
	private:
		typedef __m128 m128;

		union {
			f32 elements[9];

			vec3 columns[3];
		};

	private:
		void loadRows(m128* xmm) const;
		void loadColumns(m128* xmm) const;

	public:
		mat3();

		mat3& scale(const f32 &x, const f32 &y);
		mat3& scale(const vec2 &scale);

		mat3& rotate(const f32& z);

		friend mat3 operator*(mat3 left, const mat3 &right);
		friend vec3 operator*(mat3 left, const vec3 &right);
		friend vec2 operator*(mat3 left, const vec2 &right);

		mat3 operator*=(const mat3 &other);
		vec3 operator*=(const vec3 &other);
		vec2 operator*=(const vec2 &other);

		float& operator[](uint32 index);
	};



} }
