#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "utils/Internal.h"
#include "utils/Log.h"
#include "utils/String.h"
#include "utils/input/Input.h"

namespace ht { namespace graphics {

	class Window {
	private:
		utils::String title;
		uint16 width, height;
		GLFWwindow *window;

	public:
		Window(utils::String title, const uint16 &width, const uint16 &height);
		~Window();
		bool closed() const;
		void update();
		void clear() const;

		inline uint16 getWidth() const { return width; }
		inline uint16 getHeight() const { return height; }

		inline GLFWwindow* getWindow() const { return window; }

		inline bool compare(GLFWwindow* window) {
			return this->window == window;
		}

		inline void resize(uint16 width, uint16 height) {
			this->width = width;
			this->height = height;
		}

	private:
		bool init();
	};
} }