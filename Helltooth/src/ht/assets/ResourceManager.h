#pragma once

#include <vector>

#include "ResourceStack.h"

namespace ht { namespace assets {

	class ResourceManager {
	private:
		static ResourceManager* instance;
		std::vector<ResourceStack*> stacks;

	public:
		~ResourceManager();

		bool isAllLoaded();

		__forceinline unsigned int createStack() { stacks.push_back(htnew ResourceStack()); return stacks.size() - 1; }
		__forceinline ResourceStack* getStack(unsigned int id) { return stacks[id]; }

		__forceinline static void Init() {
			if (instance) { HT_ERROR("[ResourceManager] Reinitialization not possible!"); return; }
			instance = htnew ResourceManager();
		}

		__forceinline static ResourceManager* Get() {
			if (!instance) { Init(); HT_ERROR("[ResourceManager] ResourceManager not initialized, initialization forced!"); }
			return instance;
		}

		__forceinline static void End() {
			if (!instance) { HT_ERROR("[ResourceManager] Deletion not possible, ResourceManager not initialized!"); return; }
			instance = nullptr; del instance;
		}
	};
} }