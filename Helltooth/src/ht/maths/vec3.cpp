#include "vec3.h"
namespace ht {	namespace maths {

		vec3::vec3() {
			x = 0;
			y = 0;
			z = 0;
		}

		vec3::vec3(const float &x, const float &y, const float &z) {
			this->x = x;
			this->y = y;
			this->z = z;
		}

		vec3 operator+(vec3 left, vec3 right) {
			left.x += right.x;
			left.y += right.y;
			left.z += right.z;
			return left;
		}

		vec3 operator-(vec3 left, vec3 right) {
			left.x -= right.x;
			left.y -= right.y;
			left.z -= right.z;
			return left;
		}
		vec3 operator*(vec3 left, vec3 right) {
			left.x *= right.x;
			left.y *= right.y;
			left.z *= right.z;
			return left;
		}
} }