#include "vec2.h"

namespace ht { namespace maths {

	vec2::vec2() {
		x = 0;
		y = 0;
	}
	
	vec2::vec2(const float &x, const float &y) {
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

	void vec2::print() {
#if PRINT
		std::cout << "Vector2 x: " << x << " y: " << y << std::endl;
#endif
	}

} }