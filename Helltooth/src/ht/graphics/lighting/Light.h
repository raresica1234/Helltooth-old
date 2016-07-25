#pragma once

#include "../../maths/vec3.h"
namespace ht { namespace graphics { 

	using namespace maths;
	class Light {
	private:
		vec3 position;
		vec3 lightColor;

	public:
		Light(vec3 position, vec3 lightColor)
			: position(position), lightColor(lightColor) { }
		
		inline vec3 getPosition() const { return position; }

		inline vec3 getColor() const { return lightColor; }
	
	};

} }
