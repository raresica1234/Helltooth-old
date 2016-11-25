#pragma once
#include <iostream>
namespace ht { namespace maths {

	struct vec4 {

		float x;
		float y;
		float z;
		float w;

		vec4();
		vec4(const float &x, const float &y, const float &z, const float &w);

		friend vec4 operator+(vec4 left, vec4 &right);
		friend vec4 operator-(vec4 left, vec4 &right);
		friend vec4 operator*(vec4 left, vec4 &right);
	};
} }
