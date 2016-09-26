#pragma once
#include <iostream>

namespace ht {	namespace maths {

	struct vec2 {

		float x;
		float y;

		vec2();
		vec2(const float &x, const float &y);

		friend vec2 operator+(vec2 left, vec2& right);
		friend vec2 operator-(vec2 left, vec2& right);
		friend vec2 operator*(vec2 left, vec2& right);

		void print();
	};

} }