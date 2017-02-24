#include "Window.h"
#include "WindowManager.h"

namespace ht { namespace graphics {
	using namespace utils;

	void windowResize(GLFWwindow *window, int width, int height);

	Window::Window(String title, const int &width, const int &height) {
		this->width = width;
		this->height = height;
		this->title = title;
		if (!init()) {
			glfwTerminate();
		}
	}

	Window::~Window() {
		glfwDestroyWindow(window);
	}

	bool Window::init() {
		if (!glfwInit()) {
			HT_FATAL("Failed to initialize GLFW!");
			return false;
		}

		window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
		if (!window) {
			HT_FATAL("Failed to create GLFW Window!");
			return false;
		}

		glfwMakeContextCurrent(window);
		glfwSetWindowSizeCallback(window, windowResize);

		if (glewInit() != GLEW_OK) {
			HT_FATAL("Could not initialize GLEW!");
			return false;
		}
		HT_WARN("OpenGL Version: %s", glGetString(GL_VERSION));
		HT_WARN("OpenGL Vendor: %s", glGetString(GL_VENDOR));
		HT_WARN("GLFW Version: %i", glfwGetVersion);
		HT_WARN("GLEW  Version: %i", GLEW_VERSION);

		Input::Get()->addWindow(window);
		Input::Get()->addCallbacks();

		glfwSwapInterval(0);
		glEnable(GL_DEPTH_TEST);

		return true;
	}

	void Window::clear() const {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::update() {
		glfwPollEvents();
		glfwSwapBuffers(window);
		glViewport(0, 0, width, height);
	}

	bool Window::closed() const {
		return glfwWindowShouldClose(window) == 1;
	}

	void windowResize(GLFWwindow *window, int width, int height) {
		WindowManager::Get()->resize(window, width, height);
	}
} }