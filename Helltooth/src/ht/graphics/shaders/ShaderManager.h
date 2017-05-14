#pragma once

#include <vector>

#include "ShaderProgram.h"

#include "utils/Internal.h"
#include "utils/Log.h"
#include "utils/String.h"
#include "utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	class ShaderManager {
	private:
		std::vector<ShaderProgram*> shaders;
		static ShaderManager* sManager;

	public:
		uint32 loadProgram(utils::String vertexPath, utils::String fragmentPath, bool path = true);
		ShaderProgram* getProgram(uint32 &id);
		void cleanUP();

		void reCompile();

		__forceinline static void Init() {
			if (sManager) { HT_ERROR("[ShaderManager] Reinitialization not possible!"); return; }
			sManager = htnew ShaderManager();
		}

		__forceinline static ShaderManager* Get() {
			if (!sManager){ Init(); HT_ERROR("[ShaderManager] ShaderManager not initialized, initialization forced!"); }
			return sManager;
		}

		__forceinline static void End() {
			if (!sManager) { HT_ERROR("[ShaderManager] Deletion not possible, ShaderManager not initialized!"); return; } 
			del sManager;	
			sManager = nullptr;
		}

	};
} }