#pragma once

#include <iostream>

#include "utils/Internal.h"

namespace ht {	namespace maths {

	struct vec2 {
		f32 x, y;

		vec2();
		vec2(const f32 &x, const f32 &y);

		friend vec2 operator+(vec2 left, vec2& right);
		friend vec2 operator-(vec2 left, vec2& right);
		friend vec2 operator*(vec2 left, vec2& right);
		bool operator==(vec2 other);
		bool operator!=(vec2 other);

		__forceinline bool operator<(const vec2& other) const {
			f32 proda = x * y;
			f32 prodb = other.x * other.y;
			return proda < prodb;
		}
	};
} }

namespace std {
	template<>
	struct hash<ht::maths::vec2> {
		size_t operator()(const ht::maths::vec2 &value) const {
			return std::hash<float>()(value.x) ^ std::hash<float>()(value.y);
		}
	};

}