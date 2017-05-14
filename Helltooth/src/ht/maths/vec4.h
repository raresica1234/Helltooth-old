#pragma once

#include <iostream>

#include "utils/Internal.h"

namespace ht { namespace maths {

	struct vec4 {
		f32 x, y, z, w;

		vec4();
		vec4(const f32 &x, const f32 &y, const f32 &z, const f32 &w);

		friend vec4 operator+(vec4 left, vec4 &right);
		friend vec4 operator-(vec4 left, vec4 &right);
		friend vec4 operator*(vec4 left, vec4 &right);
	};
} }
