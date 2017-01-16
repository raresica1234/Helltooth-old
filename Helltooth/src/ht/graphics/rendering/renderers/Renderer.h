#pragma once
#include "../../Camera.h"
#include "../../shaders/ShaderProgram.h"

#include "../../../maths/mat4.h"
#include "../Entity.h"
namespace ht { namespace graphics {

	class Renderer {
	protected:
		Camera* camera = nullptr;
		ShaderProgram* program;

		maths::mat4 projectionMatrix;

		Renderer(Camera* camera, ShaderProgram* program)
			: camera(camera), program(program) { }

	public:
		void setProjection(maths::mat4 projectionMatrix) { 
			this->projectionMatrix = projectionMatrix;
		}

		virtual void submit(const Entity* e) = 0;

		virtual void prepare() = 0;
		virtual void render() = 0;
		virtual void cleanUP() = 0;
		virtual void forceCleanUP() = 0;
	};


} }

