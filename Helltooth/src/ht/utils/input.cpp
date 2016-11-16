#include "Input.h"

namespace ht { namespace utils {

		bool Input::keys[MAX_KEYS];
		bool Input::buttons[MAX_BUTTONS];
		double Input::mouseX, Input::mouseY;

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			Input::keys[key] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
			Input::mouseX = xpos;
			Input::mouseY = ypos;
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
			Input::buttons[button] = action == GLFW_PRESS;
		}

} }