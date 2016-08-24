#include "Window.h"

namespace ht { namespace graphics {

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
				HT_FATAL("Failed to initialize GLFW!");
				return false;
			}

			m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
			if (!m_Window) {
				HT_FATAL("Failed to create GLFW Window!");
				return false;
			}

			glfwMakeContextCurrent(m_Window);
			glfwSetWindowSizeCallback(m_Window, windowResize);

			if (glewInit() != GLEW_OK) {
				HT_FATAL("Could not initialize GLEW!");
				return false;
			}
			HT_WARN("OpenGL Version: %s", glGetString(GL_VERSION));
			HT_WARN("GLFW Version: %i", glfwGetVersion);
			HT_WARN("GLEW  Version: %i", GLEW_VERSION);
			utils::Input::init();

			glfwSetKeyCallback(m_Window, utils::key_callback);
			glfwSetMouseButtonCallback(m_Window, utils::mouse_button_callback);
			glfwSetCursorPosCallback(m_Window, utils::cursor_position_callback);

			glfwSwapInterval(0);
			glEnable(GL_DEPTH_TEST);

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