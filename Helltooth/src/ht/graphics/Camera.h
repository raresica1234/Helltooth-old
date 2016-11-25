#pragma once

#include "../maths/mat4.h"
#include "../utils/Input.h"
#include <GLFW/glfw3.h>

#include "window/window.h"

namespace ht { namespace graphics {

	class Camera {
	
	private:
		ht::maths::vec3 position;
		ht::maths::vec3 rotation;

		ht::maths::vec2 mouse;

		float movementSpeedFactor;

		float pitchSensitivity; 
		float yawSensitivity;
		ht::maths::vec2 midPoint;

	public:

		Camera(Window* window);

		~Camera();

		void update();

		ht::maths::mat4 generateViewMatrix() const;

	protected:
		void handleMouseMove(float mouseX, float mouseY);
	};
} }
