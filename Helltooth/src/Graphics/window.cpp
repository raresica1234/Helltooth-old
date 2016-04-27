#include "Window.h"

namespace ht {	namespace graphics {

		void windowResize(GLFWwindow *window, int width, int height);

		Window::Window(const char *title, const int &width, const int &height) {
			m_Width = width;
			m_Height = height;
			m_Title = title;
			if (!init()) {
				glfwTerminate();
			}
		}

		Window::~Window() {
			glfwDestroyWindow(m_Window);
		}

		bool Window::init() {
			if (!glfwInit()) {
				std::cout << "Could not initialize GLFW!" << std::endl;
				return false;
			}

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window) {
				std::cout << "Failed to create GLFW Window!" << std::endl;
				return false;
			}

			glfwMakeContextCurrent(m_Window);
			glfwSetWindowSizeCallback(m_Window, windowResize);

			if (glewInit() != GLEW_OK) {
				std::cout << "Could not initialize GLEW!" << std::endl;
				return false;
			}
			std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
			std::cout << "GLFW Version: " << glfwGetVersion << std::endl;
			std::cout << "GLEW  Version: " << GLEW_VERSION << std::endl;
			utils::Input::init();

			glfwSetKeyCallback(m_Window, utils::key_callback);

			return true;
		}

		void Window::clear() const {
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update() {
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
			
		}

		bool Window::closed() const {
			return glfwWindowShouldClose(m_Window) == 1;
		}

		void windowResize(GLFWwindow *window, int width, int height) {
			glViewport(0, 0, width, height);
		}
} }