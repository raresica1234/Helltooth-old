#include "vec2.h"

namespace ht { namespace maths {

	vec2::vec2() {
		x = 0;
		y = 0;
	}
	
	vec2::vec2(const f32 &x, const f32 &y) {
		this->x = x;
		this->y = y;
	}

	vec2 operator+(vec2 left, vec2 &right) {
		left.x += right.x;
		left.y += right.y;
		return left;
	}

	vec2 operator-(vec2 left, vec2 &right) {
		left.x -= right.x;
		left.y -= right.y;
		return left;
	}

	vec2 operator*(vec2 left, vec2 &right) {
		left.x *= right.x;
		left.y *= right.y;
		return left;
	}

	bool vec2::operator==(vec2 other) {
		return (x == other.x) && (y == other.y);
	}

	bool vec2::operator!=(vec2 other) {
		if (x != other.x)
			return true;
		if (y != other.y)
			return true;
		return false;
	}

} }