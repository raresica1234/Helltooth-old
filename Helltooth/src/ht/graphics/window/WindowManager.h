#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <vector>

#include "window.h"

#include "utils/Log.h"
#include "utils/String.h"

#include "utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	class WindowManager {
	private:
		std::vector<Window*> windows;
		static WindowManager* wManager;

	public:
		~WindowManager();
		unsigned int createWindow(ht::utils::String title, const int width, const int height);
		void resize(GLFWwindow* glfwwindow, int width, int height);
		Window* getWindow(unsigned int id);

		static void Init() { 
			if (!wManager)
				wManager = htnew WindowManager();
			else
				HT_WARN("[WindowManager] Reinitialization not possible!");
		}

		static WindowManager* Get() { return wManager; }

		static void End() { del wManager; wManager = nullptr; }
	};
} }
