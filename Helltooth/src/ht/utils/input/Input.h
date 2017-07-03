#pragma once

#include <GLFW/glfw3.h>
#include <iostream>

#include "utils/Internal.h"
#include "utils/memory/MemoryManager.h"

namespace ht { namespace utils {

	struct Event {
#			define MAX_KEYS 65535
#			define MAX_BUTTONS 16

		f32 mouseX = -1, mouseY = -1, scrollOffsetX = 0, scrollOffsetY = 0;

		bool keys[MAX_KEYS], mouse_buttons[MAX_BUTTONS];

		mutable bool handled = false;

		Event() {
			memset(&keys, 0, MAX_KEYS);
			memset(&mouse_buttons, 0, MAX_BUTTONS);
		}

		bool isPressed(int32 keyCode) const { return keys[keyCode]; }
		bool isButtonPressed(int32 button) const { return mouse_buttons[button]; }

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
			event.handled = false;
			return event;
		}

		friend void key_callback(GLFWwindow* window, int32 key, int32 scancode, int32 action, int32 mods) {
			event.keys[key] = action == GLFW_RELEASE ? false : true;
		}

		friend void cursor_position_callback(GLFWwindow* window, f64 xpos, f64 ypos) {
			event.mouseX = (float)xpos;
			event.mouseY = (float)ypos;
		}

		friend void mouse_button_callback(GLFWwindow* window, int32 button, int32 action, int32 mods) {
			event.mouse_buttons[button] = action == GLFW_RELEASE ? false : true;
		}

		friend void scroll_callback(GLFWwindow* window, f64 xoffset, f64 yoffset) {
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
