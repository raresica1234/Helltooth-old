#include "WindowManager.h"

namespace ht { namespace graphics {
	using namespace utils;

	WindowManager* WindowManager::wManager = nullptr;

	WindowManager::~WindowManager() {
		for (Window* window : windows)
			del window;
	}
	
	unsigned int WindowManager::createWindow(String title, const uint16 width, const uint16 height) {
		windows.push_back(htnew Window(title, width, height));
		return windows.size() - 1;
	}
	
	void WindowManager::resize(GLFWwindow* glfwwindow, uint16 width, uint16 height) {
		for (Window* window : windows)
			if (window->compare(glfwwindow)) 
				window->resize(width, height);
	}

	Window* WindowManager::getWindow(uint32 id) {
		if (id > windows.size())
			HT_FATAL("Window id %i is bigger than vector size %i", id, windows.size());
		return windows[id];
	}

} }

