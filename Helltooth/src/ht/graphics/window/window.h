#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../../utils/Log.h"
#include "../../utils/Input.h"

namespace ht { namespace graphics {

		class Window {
		private:
			const char* title;
			int width;
			int height;
			GLFWwindow *window;
			
		public:
			Window(const char *title, const int &width, const int &height);
			~Window();
			bool closed() const;
			void update();
			void clear() const;

			inline int getWidth() const { return width; }
			inline int getHeight() const { return height; }

			inline GLFWwindow* getWindow() const { return window; }

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