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

		bool vec3::operator==(vec3 other) {
			return (x == other.x) && (y == other.y) && (z == other.z);
		}

		bool vec3::operator!=(vec3 other) {
			if (x != other.x)
				return true;
			if (y != other.y)
				return true;
			if (z != other.z)
				return true;
			return false;
		}

} }