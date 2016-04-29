#include "Input.h"

namespace ht { namespace utils {

	bool Input::m_Keys[MAX_KEYS];
	bool Input::m_Buttons[MAX_BUTTONS];
	double Input::mouseX, Input::mouseY;

	void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		Input::m_Keys[key] = action != GLFW_RELEASE;
	}

	void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		Input::mouseX = xpos;
		Input::mouseY = ypos;
	}

	void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		Input::m_Buttons[button] = action == GLFW_PRESS;
	}

} }