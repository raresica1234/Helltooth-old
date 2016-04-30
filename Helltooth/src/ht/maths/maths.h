#pragma once

const double PI = 3.14159265358979323846;

namespace ht { namespace maths {

	inline float toRadians(float degrees) { return degrees * (float)(PI / 180.0f); }
	inline float toDegrees(float radians) { return radians * (float)(180.0f / PI); }

} }