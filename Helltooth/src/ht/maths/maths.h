#pragma once

const double PI = 3.1415926535897932384626433832;

namespace ht { namespace maths {

	inline float toRadians(float degrees) { return degrees * (float)(PI / 180.0f); }
	inline float toDegrees(float radians) { return radians * (float)(180.0f / PI); }

} }