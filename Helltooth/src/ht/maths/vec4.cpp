#include "vec4.h"

namespace ht { namespace maths {

	vec4::vec4() {
		x = 0;
		y = 0;
		z = 0;
		w = 0;
	}

	vec4::vec4(const float &x, const float &y, const float &z, const float &w) {
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	vec4 operator+(vec4 left, vec4 &right) {
		left.x += right.x;
		left.y += right.y;
		left.z += right.z;
		left.w += right.w;
		return left;
	}

	vec4 operator-(vec4 left, vec4 &right) {
		left.x -= right.x;
		left.y -= right.y;
		left.z -= right.z;
		left.w -= right.w;
		return left;
	}
	vec4 operator*(vec4 left, vec4 &right) {
		left.x *= right.x;
		left.y *= right.y;
		left.z *= right.z;
		left.w *= right.w;
		return left;
	}
	
	void vec4::print() {
#if PRINT
		std::cout << "Vector4 x: " << x << " y: " << y << " z: " << z << " w: " << w << std::endl;
#endif
	}

} }