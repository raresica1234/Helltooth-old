#pragma once

#include <iostream>

#include "utils/Internal.h"

namespace ht {	namespace maths {

	struct vec3 {

		f32 x, y, z;

		vec3();
		vec3(const f32 &x, const f32 &y, const f32 &z);

		friend vec3 operator+(vec3 left, vec3 right);
		friend vec3 operator-(vec3 left, vec3 right);
		friend vec3 operator*(vec3 left, vec3 right);
		bool operator==(const vec3 other) const;
		bool operator!=(const vec3 other) const;

		inline f32 length() {
			return sqrt(x * x + y * y + z * z);
		}

		inline void normalize() {
			f32 length = this->length();
			if (length != 0) {
				this->x = x / length;
				this->y = y / length;
				this->z = z / length;
			}
		}
	};
} }