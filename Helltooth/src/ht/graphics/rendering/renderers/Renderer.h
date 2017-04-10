#pragma once

#include "../Entity.h"
#include "../Light.h"

#include "../../Camera.h"

#include "../../shaders/ShaderProgram.h"

#include "maths/mat4.h"

namespace ht { namespace graphics {

	class Renderer {
	protected:
		Camera* camera = nullptr;
		ShaderProgram* program;

		maths::mat4 projectionMatrix;

		Renderer(Camera* camera, ShaderProgram* program)
			: camera(camera), program(program) {
			reloadTextures();
		}

		Renderer(Camera* camera, unsigned int programID)
			: camera(camera), program(ShaderManager::Get()->getProgram(programID)) {
			reloadTextures();
		}

		std::vector<Light*> lights;

	public:
		void setProjection(maths::mat4 projectionMatrix) { 
			this->projectionMatrix = projectionMatrix;
		}

		virtual void submit(const Entity* e) = 0;

		virtual void prepare() = 0;
		virtual void render() = 0;
		virtual void cleanUP() = 0;
		virtual void forceCleanUP() = 0;

		virtual void addLight(Light* light) {
			lights.push_back(light);
		}

		void reloadTextures() {
			program->start();
			GLint texIDs[] = {
				0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31
			};
			program->uniform1iv("textures", texIDs, 32);
			program->uniform1f("density", API::getFog().density);
			program->uniform1f("gradient", API::getFog().gradient);
			program->uniform4f("skyColor", maths::vec4(.3f, .4f, .7f, 1.f));
		}

		virtual void popLight() {
			lights.pop_back();
		}

	};


} }

