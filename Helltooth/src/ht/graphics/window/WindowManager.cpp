#include "WindowManager.h"


namespace ht { namespace graphics {

	std::vector<Window*> WindowManager::windows;

	unsigned int WindowManager::createWindow(String title, const int width, const int height) {
		windows.push_back(htnew Window(title, width, height));
		return windows.size() - 1;
	}
	
	void WindowManager::resize(GLFWwindow* glfwwindow, int width, int height) {
		for (Window* window : windows)
			if (window->compare(glfwwindow)) 
				window->resize(width, height);
	}


	Window* WindowManager::getWindow(unsigned int &id) {
		if (id > windows.size())
			HT_FATAL("Window id %i is bigger than vector size %i", id, windows.size());
		return windows[id];
	}


	void WindowManager::cleanUP() {
		for (Window* window : windows)
			del window;
	}


} }

