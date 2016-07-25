#pragma once

#include "../../maths/vec3.h"


namespace ht { namespace graphics { 
	using namespace maths;

	class Sun {
	private:
		vec3 position;

	public:
		Sun(vec3 positon)
			: position(position) { }

		inline vec3 getPosition() const { return position; }
	};


} }
