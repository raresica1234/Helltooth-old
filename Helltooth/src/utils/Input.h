#pragma once
#include <GLFW/glfw3.h>

#ifndef MAX_KEYS
#define MAX_KEYS	 1000
#endif

#ifndef MAX_BUTTONS
#define MAX_BUTTONS	 8
#endif

namespace ht { namespace utils {

	class Input {

	private:
		static bool m_Keys[MAX_KEYS];
		static bool m_Buttons[MAX_BUTTONS];
		static double mouseX, mouseY;
	public:
		static friend void init();
		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
	};


} }
