#include "Camera.h"

namespace ht { namespace graphics {
	using namespace utils;
	using namespace maths;

	Camera::Camera(Window* window)
		: position(0.0, -5.0, 0.0), rotation() {
		movementSpeedFactor = 10.0f; // How fast we move (higher values mean we move and strafe faster)

		pitchSensitivity = 0.2f; // How sensitive mouse movements affect looking up and down
		yawSensitivity = 0.2f; // How sensitive mouse movements affect looking left and right
		midPoint.x = (f32)window->getWidth() / 2;
		midPoint.y = (f32)window->getHeight() / 2;
	}

	Camera::~Camera() {}

	void Camera::update(const Event& e) {
		mouse = vec2(e.mouseX, e.mouseY);

		if (e.isButtonPressed(GLFW_MOUSE_BUTTON_2))
			handleMouseMove(mouse.x, mouse.y);

		midPoint.x = mouse.x;
		midPoint.y = mouse.y;

		vec3 movement;

		f32 sinXRot = sin(toRadians(rotation.x));
		f32 cosXRot = cos(toRadians(rotation.x));

		f32 sinYRot = sin(toRadians(rotation.y));
		f32 cosYRot = cos(toRadians(rotation.y));

		if (e.isPressed(GLFW_KEY_W)) {
			movement.x += sinYRot * cosXRot;
			movement.y += sinXRot;
			movement.z += cosYRot * cosXRot;
		}

		if (e.isPressed(GLFW_KEY_S)) {
			movement.x += -sinYRot * cosXRot;
			movement.y += -sinXRot;
			movement.z += -cosYRot * cosXRot;
		}


		if (e.isPressed(GLFW_KEY_A)) {
			movement.x += cosYRot;
			movement.z += -sinYRot;
		}

		if (e.isPressed(GLFW_KEY_D)) {
			movement.x += -cosYRot;
			movement.z += sinYRot;
		}

		movement.normalize();

		movement = vec3(movement.x * movementSpeedFactor, movement.y * movementSpeedFactor, movement.z * movementSpeedFactor);

		position.x += movement.x;
		position.y += movement.y;
		position.z += movement.z;

		viewMatrix = mat4().rotate(rotation).translate(position);
	}

	mat4 Camera::generateViewMatrix() const {
		return viewMatrix;
	}

	void Camera::handleMouseMove(f32 mouseX, f32 mouseY) {
		// Calculate our horizontal and vertical mouse movement from middle of the window
		float horizMovement = (mouseX - midPoint.x) * yawSensitivity;
		float vertMovement = (mouseY - midPoint.y) * pitchSensitivity;


		rotation.x += vertMovement;
		rotation.y -= horizMovement;

		if (rotation.x < -90) {
			rotation.x = -90;
		}
		if (rotation.x > 90) {
			rotation.x = 90;
		}

		if (rotation.y < 0) {
			rotation.y += 360;
		}
		if (rotation.y > 360) {
			rotation.y += -360;
		}

		//glfwSetCursorPos(window->getWindow(), midPoint.x, midPoint.y);

	}


} }