#pragma once

#include "maths/vec2.h"
#include "maths/vec3.h"
#include "maths/maths.h"

namespace ht { namespace graphics {
	enum LIGHT_TYPE {
		LIGHT_TYPE_NONE,
		LIGHT_TYPE_DIRECTIONAL,
		LIGHT_TYPE_POINT,
		LIGHT_TYPE_SPOT
	};

	class Light {
	protected:
		maths::vec3 color;
		LIGHT_TYPE lightType;

	public:
		Light(const maths::vec3& color) : color(color), lightType(LIGHT_TYPE_NONE) {}

		__forceinline maths::vec3& getColor() { return color; }

		__forceinline int getLightType() { return lightType; }

	};

	class DirectionalLight : public Light {
	private:
		maths::vec3 direction;

	public:
		DirectionalLight(const maths::vec3& color, const maths::vec3& direction) : Light(color), direction(direction) { lightType = LIGHT_TYPE_DIRECTIONAL; }

		__forceinline maths::vec3& getDirection() { return direction; }

	};

	class PointLight : public Light {
	protected:
		maths::vec3 position;
		maths::vec3 attenuation;

	public:
		PointLight(const maths::vec3& position, const maths::vec3& color, const maths::vec3& attenuation) 
			: Light(color), position(position), attenuation(attenuation) {
			lightType = LIGHT_TYPE_POINT;
		}

		__forceinline maths::vec3& getPosition() { return position; }

		__forceinline maths::vec3& getAttenuation() { return attenuation; }
	};

	class SpotLight : public PointLight {
	private:
		maths::vec3 direction;
		maths::vec2 cutOffExponent;

	public:
		SpotLight(const maths::vec3& position, const maths::vec3& color, const maths::vec3& direction, const maths::vec3& attenuation, const maths::vec2 cutOffExponent)
			: PointLight(position, color, attenuation), direction(direction) {
			this->cutOffExponent.x = (float)cosf(maths::toRadians(cutOffExponent.x));
			this->cutOffExponent.y = cutOffExponent.y;
			lightType = LIGHT_TYPE_SPOT;
		}

		__forceinline maths::vec2& getCutoffExponent() { return cutOffExponent; }
		__forceinline maths::vec3& getDirection() { return direction; }
		__forceinline float& getCutoff() { return cutOffExponent.x; }
		__forceinline float& getExponent() { return cutOffExponent.y; }
	};
} }

