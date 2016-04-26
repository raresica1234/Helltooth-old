#include "Window.h"

using namespace ht;
using namespace graphics;

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

bool Window::closed() const {
	return glfwWindowShouldClose(m_Window) == 1;
}

bool Window::init() {
	if (!glfwInit()) {
		std::cout << "Couldn't initialize GLFW!" << std::endl;
		return false;
	}

	m_Window = glfwCreateWindow(m_Width, m_Height, m_Title, NULL, NULL);
	if (!m_Window) {
		std::cout << "Failed to create GLFW Window!" << std::endl;
		return false;
	}

	glfwMakeContextCurrent(m_Window);
	return true;
}

void Window::update() const{
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void Window::clear() const {
	glClear(COLOR_BUFFER_BIT);
}