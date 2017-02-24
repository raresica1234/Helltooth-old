#include "Input.h"

namespace ht { namespace utils {

	Input* Input::input = nullptr;
	Event Input::event = Event();

	Input::Input() {
		event = Event();
	}

	Input::~Input() {

	}

	void Input::addWindow(GLFWwindow* window) {
		this->window = window;
	}

	void Input::addCallbacks() {
		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		glfwSetScrollCallback(window, scroll_callback);
	}
} }