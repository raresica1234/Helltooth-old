#pragma once

#include <GLFW\glfw3.h>
#include <GL\GL.h>
#include <iostream>

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
			void update() const;
			void clear() const;
		private:
			bool init();
		};


	
}}