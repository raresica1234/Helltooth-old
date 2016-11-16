#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "window.h"

#include <vector>
#include "../../utils/memory/MemoryManager.h"

#include "../../utils/Log.h"
#include "../../utils/String.h"
namespace ht { namespace graphics {

	using namespace utils;

	class WindowManager {
	private:
		static std::vector<Window*> windows;

	public:
		static unsigned int createWindow(String title, const int width, const int height);
		static void resize(GLFWwindow* glfwwindow, int width, int height);
		static Window* getWindow(unsigned int &id);
		static void cleanUP();

	};

} }
