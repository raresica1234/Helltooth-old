#pragma once

#include "utils/Internal.h"
const ht::f64 PI = 3.1415926535897932384626433832;

#include <intrin.h>

namespace ht { namespace maths {

	__forceinline f32 toRadians(const f32& degrees) { return degrees * (f32)(PI / 180.0f); }
	__forceinline f32 toDegrees(const f32& radians) { return radians * (f32)(180.0f / PI); }

} }