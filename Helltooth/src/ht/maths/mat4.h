#pragma once

#include <math.h>

#include <GL/glew.h>

#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "maths.h"

#include "utils/Internal.h"

namespace ht { namespace maths {

	struct mat4 {
	private:
		typedef __m128 m128;

	public:
		union {
			f32 elements[4 * 4];
			vec4 columns[4];
		};
		
		mat4();

	private:
		void loadRows(m128* xmm) const;
		void loadColumns(m128* xmm) const;

	public:
		static mat4 createPerspective(const f32 &FOV, const f32 &NEAR_PLANE, const f32 &FAR_PLANE, const f32 &ASPECT_RATIO);
		static mat4 createOrthographic(const f32 &left, const f32 &right, const f32 &top, const f32 &bottom, const f32 &near, const f32 &far);
		
		mat4& translate(const f32 &x, const f32 &y, const f32 &z);
		mat4& translate(const vec3 &translation);

		mat4& scale(const f32 &x, const f32 &y, const f32 &z);
		mat4& scale(const vec3 &scale);

		mat4& rotate(const f32 &x, const f32 &y, const f32 &z);
		mat4& rotate(const vec3 &axis);

		friend mat4 operator*(mat4 left, const mat4 &right);
		friend vec4 operator*(mat4 left, const vec4 &right);
		friend vec3 operator*(mat4 left, const vec3 &right);
		friend vec2 operator*(mat4 left, const vec2 &right);

		mat4 operator*=(const mat4 &other);
		vec4 operator*=(const vec4 &other);
		vec3 operator*=(const vec3 &other);
		vec2 operator*=(const vec2 &other);

		f32& operator[](uint32 index);
	};
} }
