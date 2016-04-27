#include "Input.h"

namespace ht { namespace utils {

	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if(key < MAX_KEYS)
			if (mods != GLFW_RELEASE)
				Input::m_Keys[key] = true;
			else
				Input::m_Keys[key] = false;
	}

	static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
		Input::mouseX = xpos;
		Input::mouseY = ypos;
	}

	static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
		Input::m_Buttons[button] = action == GLFW_PRESS;
	}

} }