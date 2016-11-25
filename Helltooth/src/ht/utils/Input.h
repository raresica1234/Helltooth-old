#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include "../maths/vec2.h"

#ifndef MAX_KEYS
#define MAX_KEYS	 1000
#endif

#ifndef MAX_BUTTONS
#define MAX_BUTTONS	 8
#endif


namespace ht { namespace utils {

	class Input {
	private:
		static bool keys[MAX_KEYS];
		static bool buttons[MAX_BUTTONS];
		static double mouseX, mouseY;

	public:
		inline static void init() {
			for (int i = 0; i < MAX_KEYS; i++) {
				Input::keys[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++) {
				Input::buttons[i] = false;
			}
		}

		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

		inline static bool getKey(unsigned int const &a) { return Input::keys[a]; }

		inline static bool getButton(unsigned int const &a) { return Input::buttons[a]; }

		inline static maths::vec2 getPosition() { return maths::vec2((float)mouseX, (float)mouseY); }
	};
} }
