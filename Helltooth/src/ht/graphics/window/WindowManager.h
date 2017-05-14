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
		uint32 createWindow(ht::utils::String title, const uint16 width, const uint16 height);
		void resize(GLFWwindow* glfwwindow, uint16 width, uint16 height);
		Window* getWindow(uint32 id);

		static void Init() { 
			if (wManager) {
				HT_ERROR("[WindowManager] Reinitialization not possible!"); return;
			}
			wManager = htnew WindowManager();
			
		}

		static WindowManager* Get() {
			if (!wManager) { Init(); HT_ERROR("[WindowManager] WindowManager not initialized, initialization forced!"); }
			return wManager;
		}

		static void End() {
			if (!wManager) { HT_ERROR("[WindowManager] Deletion not possible, WindowManager not initialized!"); return; }
			del wManager;
			wManager = nullptr;
		}
	};
} }
