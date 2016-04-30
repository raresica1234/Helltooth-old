#pragma once

#include <math.h>

#include <GL/glew.h>

#include "vec4.h"
#include "vec3.h"
#include "vec2.h"
#include "maths.h"

namespace ht { namespace maths {

	struct mat4 {

		union {
			GLfloat elements[4 * 4];
			vec4 columns[4];
		};
		
		mat4();

		static mat4 createPerspective(const float &FOV, const float &NEAR_PLANE, const float &FAR_PLANE, const float &ASPECT_RATIO);
		static mat4 createOrthographic(const float &left, const float &right, const float &top, const float &bottom, const float &near, const float &far);
		static mat4 createIdentity();

		void translate(const vec3 &translation);
		void scale(const vec3 &scale);
		void rotate(const float &angle, const vec3 &axis);

		friend mat4 operator*(mat4 left, const mat4 &right);
		friend vec4 operator*(mat4 left, const vec4 &right);
		friend vec3 operator*(mat4 left, const vec3 &right);
		friend vec2 operator*(mat4 left, const vec2 &right);

		mat4 operator*=(const mat4& other);
		vec4 operator*=(const vec4 &other);
		vec3 operator*=(const vec3 &other);
		vec2 operator*=(const vec2 &other);

		inline void print() const {
			std::cout << std::endl;
			for (int i = 1; i <= 16; i++) {
				std::cout << elements[i - 1] << " ";
				if (i % 4 == 0)
					std::cout << std::endl;
			}
		}
	};

} }