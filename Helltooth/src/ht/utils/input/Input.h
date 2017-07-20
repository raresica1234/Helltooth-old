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

		mutable bool previously_pressed[MAX_KEYS], keys[MAX_KEYS], mouse_buttons[MAX_BUTTONS];

		mutable bool handled = false;

		Event() {
			memset(&keys, 0, MAX_KEYS);
			memset(&previously_pressed, 0, MAX_KEYS);
			memset(&mouse_buttons, 0, MAX_BUTTONS);
		}

		bool isHold(uint16 key) const { return previously_pressed[key] || keys[key]; }
		bool isPressed(uint16 key) const {
			if (!previously_pressed[key] && keys[key]) {
				printf("Why %s tho %s\n", previously_pressed[key] == false ? "false" : "true", keys[key] == false ? "false" : "true");
				previously_pressed[key] = true;
				keys[key] = false;
				return true;
			}
			return keys[key];
		}

		static char toChar(uint32 glfwKey) {
			return glfwGetKeyName(glfwKey, 0)[0];
		}

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
			if (action == GLFW_RELEASE) {
				event.keys[key] = false;
				event.previously_pressed[key] = false;
			}
			else {
				if (!event.previously_pressed[key] && !event.keys[key]) {
					event.keys[key] = true;
				}
			}
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
