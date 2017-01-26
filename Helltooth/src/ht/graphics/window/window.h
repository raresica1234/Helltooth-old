#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../../utils/Log.h"
#include "../../utils/Input.h"
#include "../../utils/String.h"

namespace ht { namespace graphics {

	class Window {
	private:
		ht::utils::String title;
		int width;
		int height;
		GLFWwindow *window;

	public:
		Window(ht::utils::String title, const int &width, const int &height);
		~Window();
		bool closed() const;
		void update();
		void clear() const;

		inline int getWidth() const { return width; }
		inline int getHeight() const { return height; }

		inline GLFWwindow* getWindow() const { return window; }

		__forceinline maths::vec2 getDPI() {
			HDC m = GetDC(0);

			int x = GetDeviceCaps(m, LOGPIXELSX);
			int y = GetDeviceCaps(m, LOGPIXELSY);

			ReleaseDC(0, m);

			return maths::vec2(x, y);
		}

		inline bool compare(GLFWwindow* window) {
			return this->window == window;
		}

		inline void resize(int width, int height) {
			this->width = width;
			this->height = height;
		}

	private:
		bool init();
	};
} }