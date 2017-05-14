#pragma once

#include <vector>

#include "ShaderProgram.h"

#include "utils/Log.h"
#include "utils/String.h"
#include "utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	class ShaderManager {
	private:
		std::vector<ShaderProgram*> shaders;
		static ShaderManager* sManager;

	public:
		unsigned int loadProgram(ht::utils::String vertexPath, ht::utils::String fragmentPath, bool path = true);
		ShaderProgram* getProgram(unsigned int &id);
		void cleanUP();

		void reCompile();

		static void Init() {
			if (!sManager)
				sManager = htnew ShaderManager();
			else
				HT_ERROR("[ShaderManager] Reinitialization not possible!");
		}

		static ShaderManager* Get() {
			if (!sManager){
				Init();
				HT_ERROR("[ShaderManager] ShaderManager not initialized, initialization forced.");
			}
			return sManager;
		}

		static void End() { 
			if (sManager) {
				del sManager;	
				sManager = nullptr;
			} 
			else
				HT_ERROR("[ShaderManager] Deletion not possible, ShaderManager not initialized!");
		}

	};
} }