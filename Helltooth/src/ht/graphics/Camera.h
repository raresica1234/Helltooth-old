#pragma once

#include "../maths/mat4.h"
#include "../utils/Input.h"
#include <GLFW/glfw3.h>

#include "window/window.h"

namespace ht { namespace graphics {

	using namespace maths;
	using namespace utils;


	class Camera {
	
	private:
		vec3 position;
		vec3 rotation;

		vec2 mouse;

		float movementSpeedFactor;

		float pitchSensitivity; 
		float yawSensitivity;
		vec2 midPoint;

	public:

		Camera(Window* window);

		~Camera();

		void update();

		mat4 generateViewMatrix() const;

	protected:
		void handleMouseMove(float mouseX, float mouseY);
	};


} }
