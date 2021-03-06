#pragma once

#include "audio/AudioManager.h"

#include "maths/mat4.h"
#include "utils/input/Input.h"

#include <GLFW/glfw3.h>

#include "window/window.h"

namespace ht { namespace graphics {

	class Camera {
	
	private:
		maths::vec3 position, rotation;
		maths::vec2 mouse, midPoint;

		f32 movementSpeedFactor, pitchSensitivity, yawSensitivity;

		maths::mat4 viewMatrix;

	public:
		Camera(Window* window);
		~Camera();

		void update(const utils::Event& e);
		maths::mat4 generateViewMatrix() const;

		__forceinline maths::vec3 getDirection() {
			maths::mat4 rot = maths::mat4().rotate(rotation);
			return maths::vec3(-rot[2 + 0 * 4], -rot[2 + 1 * 4], -rot[2 + 2 * 4]);
		}

		__forceinline maths::vec3 getPosition() { return maths::vec3(-position.x, -position.y, -position.z); }

	protected:
		void handleMouseMove(f32 mouseX, f32 mouseY);
	};
} }
