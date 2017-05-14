#pragma once

#include "maths/vec2.h"
#include "maths/vec3.h"
#include "maths/maths.h"

#include "utils/String.h"

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
		__forceinline Light(const maths::vec3& color) : color(color), lightType(LIGHT_TYPE_NONE) {}

		__forceinline maths::vec3& getColor() { return color; }

		__forceinline int getLightType() { return lightType; }

		__forceinline virtual void uniform(utils::String name, ShaderProgram* program) {
			//program->uniform1i((name + ".type").c_str(), (int)lightType);
			program->uniform3f((name + ".color").c_str(), color);
		}
	};

	class DirectionalLight : public Light {
	private:
		maths::vec3 direction;

	public:
		__forceinline DirectionalLight(const maths::vec3& color, const maths::vec3& direction) : Light(color), direction(direction) { lightType = LIGHT_TYPE_DIRECTIONAL; }

		__forceinline maths::vec3& getDirection() { return direction; }

		__forceinline void uniform(utils::String name, ShaderProgram* program) override {
			Light::uniform(name, program);
			program->uniform3f((name + ".direction").c_str(), direction);
		}

		__forceinline void setDirection(maths::vec3& direction) { this->direction = direction; }

	};

	class PointLight : public Light {
	protected:
		maths::vec3 position;
		maths::vec3 attenuation;

	public:
		__forceinline PointLight(const maths::vec3& position, const maths::vec3& color, const maths::vec3& attenuation)
			: Light(color), position(position), attenuation(attenuation) {
			lightType = LIGHT_TYPE_POINT;
		}

		__forceinline maths::vec3& getPosition() { return position; }

		__forceinline maths::vec3& getAttenuation() { return attenuation; }

		__forceinline virtual void uniform(utils::String name, ShaderProgram* program) override {
			Light::uniform(name, program);
			program->uniform3f((name + ".position").c_str(), position);
			program->uniform3f((name + ".attenuation").c_str(), attenuation);
		}

		__forceinline void setAttenuation(maths::vec3 &attenuation) { this->attenuation = attenuation; }
	};

	class SpotLight : public PointLight {
	private:
		maths::vec3 direction;
		maths::vec2 cutOffExponent;

	public:
		__forceinline SpotLight(const maths::vec3& position, const maths::vec3& color, const maths::vec3& direction, const maths::vec3& attenuation, const maths::vec2 cutOffExponent)
			: PointLight(position, color, attenuation), direction(direction) {
			this->cutOffExponent.x = (float)cosf(maths::toRadians(cutOffExponent.x));
			this->cutOffExponent.y = cutOffExponent.y;
			lightType = LIGHT_TYPE_SPOT;
		}

		__forceinline maths::vec2& getCutoffExponent() { return cutOffExponent; }
		__forceinline maths::vec3& getDirection() { return direction; }
		__forceinline float& getCutoff() { return cutOffExponent.x; }
		__forceinline float& getExponent() { return cutOffExponent.y; }

		__forceinline void setCutoffExponent(maths::vec2 &cutoffExponent) { this->cutOffExponent = cutoffExponent; }
		__forceinline void setDirection(maths::vec3 &direction) { this->direction = direction; }
		__forceinline void setColor(maths::vec3 &color) { this->color = color; }

		__forceinline void uniform(utils::String name, ShaderProgram* program) override {
			PointLight::uniform(name, program);
			program->uniform3f((name + ".direction").c_str(), direction);
			program->uniform2f((name + ".cutoffExponent").c_str(), cutOffExponent);
		}
	};

	class LightStack {
		std::vector<Light*> lights;

	public:
		LightStack() {
			lights.reserve(32);
		}

		__forceinline void pushLight(Light* light) { lights.push_back(light); }

		__forceinline Light* operator[](uint32 id) { return lights[id]; }

		__forceinline void uniform(utils::String name, ShaderProgram* program) {
			for (uint32 i = 0; i < lights.size(); i++) {
				std::string current = std::to_string(i);
				utils::String currentName = name + "[" + utils::String(current.c_str()) + "]";
				lights[i]->uniform(currentName, program);
			}
		}

		__forceinline void popLight() { lights.pop_back(); }
		__forceinline void clear() { lights.clear(); }
		__forceinline uint32 size() { return lights.size(); }
	};

} }

