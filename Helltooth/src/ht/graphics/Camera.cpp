#include "Camera.h"

namespace ht { namespace graphics {

	Camera::Camera(Window* window)
		: position(0.0, -5.0, 0.0), rotation() {
		movementSpeedFactor = 1.0f; // How fast we move (higher values mean we move and strafe faster)

		pitchSensitivity = 0.2f; // How sensitive mouse movements affect looking up and down
		yawSensitivity = 0.2f; // How sensitive mouse movements affect looking left and right
		midPoint.x = (float)window->getWidth() / 2;
		midPoint.y = (float)window->getHeight() / 2;
	}

	Camera::~Camera() {}

	void Camera::update() {
		mouse = Input::getPosition();

		if (Input::getButton(GLFW_MOUSE_BUTTON_2))
			handleMouseMove(mouse.x, mouse.y);

		midPoint.x = mouse.x;
		midPoint.y = mouse.y;

		vec3 movement;

		float sinXRot = sin(toRadians(rotation.x));
		float cosXRot = cos(toRadians(rotation.x));

		float sinYRot = sin(toRadians(rotation.y));
		float cosYRot = cos(toRadians(rotation.y));

		if (Input::getKey(GLFW_KEY_W)) {
			movement.x += sinYRot * cosXRot;
			movement.y += sinXRot;
			movement.z += cosYRot * cosXRot;
		}

		if (Input::getKey(GLFW_KEY_S)) {
			movement.x += -sinYRot * cosXRot;
			movement.y += -sinXRot;
			movement.z += -cosYRot * cosXRot;
		}


		if (Input::getKey(GLFW_KEY_A)) {
			movement.x += cosYRot;
			movement.z += -sinYRot;
		}

		if (Input::getKey(GLFW_KEY_D)) {
			movement.x += -cosYRot;
			movement.z += sinYRot;
		}

		movement.normalize();

		movement = vec3(movement.x * movementSpeedFactor, movement.y * movementSpeedFactor, movement.z * movementSpeedFactor);

		position.x += movement.x;
		position.y += movement.y;
		position.z += movement.z;

	}

	mat4 Camera::generateViewMatrix() const {
		mat4 rotation = mat4::createIdentity();
		rotation.rotate(vec3(this->rotation.x, this->rotation.y, this->rotation.z));

		mat4 translation = mat4::createIdentity();
		translation.translate(vec3(position.x, position.y, position.z));
		return rotation * translation;
	}

	void Camera::handleMouseMove(float mouseX, float mouseY) {
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