#pragma once
#include "vec4.h"

namespace ht { namespace maths {

	struct mat4 {

		union elements {
			float elements[4 * 4];
			vec4 columns[4];
		};


	};

} }
