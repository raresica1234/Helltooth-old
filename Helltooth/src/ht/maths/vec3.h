#pragma once
#include <iostream>

namespace ht {	namespace maths {

		struct vec3 {

			float x;
			float y;
			float z;

			vec3();
			vec3(const float &x, const float &y, const float &z);

			friend vec3 operator+(vec3 left, vec3 right);
			friend vec3 operator-(vec3 left, vec3 right);
			friend vec3 operator*(vec3 left, vec3 right);

			void print();
		};

} }