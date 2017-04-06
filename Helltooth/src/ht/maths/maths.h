#pragma once

const double PI = 3.1415926535897932384626433832;

#include <intrin.h>

namespace ht { namespace maths {

	__forceinline float toRadians(const float& degrees) { return degrees * (float)(PI / 180.0f); }
	__forceinline float toDegrees(const float& radians) { return radians * (float)(180.0f / PI); }

} }