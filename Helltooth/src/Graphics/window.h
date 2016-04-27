#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "../utils/Input.h"

namespace ht { namespace graphics {

		class Window {
		private:
			const char* m_Title;
			int m_Width;
			int m_Height;
			GLFWwindow *m_Window;
			bool m_Closed;
			
		public:
			Window(const char *title, const int &width, const int &height);
			~Window();
			bool closed() const;
			void update();
			void clear() const;

			inline int getWidth() const { return m_Width; }
			inline int getHeight() const { return m_Height; }

		private:
			bool init();
		};
} }