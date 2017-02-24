#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

#include "utils/memory/MemoryManager.h"

namespace ht { namespace utils {

	struct Event {
#			define MAX_KEYS 65535
#			define MAX_BUTTONS 16

		float mouseX = -1, mouseY = -1;

		float scrollOffsetX = 0, scrollOffsetY = 0;

		bool keys[MAX_KEYS];
		bool mouse_buttons[MAX_BUTTONS];
		Event() {
			memset(&keys, 0, MAX_KEYS);
			memset(&mouse_buttons, 0, MAX_BUTTONS);
		}

		bool isPressed(int keyCode) const { return keys[keyCode]; }
		bool isButtonPressed(int button) const { return mouse_buttons[button]; }

	};

	class Input {
	private:
		static Input* input;

		GLFWwindow* window = nullptr;

		static Event event;
	public:
		
		Input();
		~Input();

		void addWindow(GLFWwindow* window);

		void addCallbacks();

		const Event& pullEvents() {
			return event;
		}

		friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			event.keys[key] = action == GLFW_PRESS ? true : false;
		}

		friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {
			event.mouseX = (float)xpos;
			event.mouseY = (float)ypos;
		}

		friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
			event.mouse_buttons[button] = action == GLFW_PRESS ? true : false;
		}

		friend void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
			printf("%.2f %.2f", xoffset, yoffset);
		}

		__forceinline static void Init() {
			if (!input)
				input = htnew Input();
			else
				HT_ERROR("[Input] Input is already initialized");
		}

		__forceinline static Input* Get() {
			if (!input)
				Init();
			return input;
		}

		__forceinline static void End() {
			if (input)
				del input;
			else
				HT_ERROR("[Input] Input was not initialized");
		}


	};
} }
