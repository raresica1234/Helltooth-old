#pragma once
#include <iostream>
#include <map>

namespace ht {	namespace maths {

	struct vec2 {

		float x;
		float y;

		vec2();
		vec2(const float &x, const float &y);

		friend vec2 operator+(vec2 left, vec2& right);
		friend vec2 operator-(vec2 left, vec2& right);
		friend vec2 operator*(vec2 left, vec2& right);
		bool operator==(vec2 other);
		bool operator!=(vec2 other);

		__forceinline bool operator<(const vec2& other) const {
			float proda = x * y;
			float prodb = other.x * other.y;
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