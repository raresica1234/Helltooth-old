#pragma once

#include "ResourceStack.h"

namespace ht { namespace assets {

	class ResourceManager {
	private:
		static ResourceManager* instance;
		std::vector<ResourceStack*> stacks;

	public:
		~ResourceManager() {
			for (ResourceStack* stack : stacks)
				del stack;
		}

		__forceinline unsigned int createStack() { stacks.push_back(htnew ResourceStack()); return stacks.size() - 1; }

		__forceinline ResourceStack* getStack(unsigned int id) { return stacks[id]; }

		bool isAllLoaded();

		__forceinline static void Init() {
			if (!instance)
				instance = htnew ResourceManager();
			else
				HT_ERROR("[ResourceManager] Reinitialization not possible!");
		}

		__forceinline static ResourceManager* Get() {
			if (!instance) {
				Init();
				HT_ERROR("[ResourceManager] ResourceManager not initialized, initialization forced.");
			}
			return instance;
		}

		__forceinline static void End() {
			if (instance) {
				del instance;
				instance = nullptr;
			}
			else
				HT_ERROR("[ResourceManager] Deletion not possible, ResourceManager not initialized!");
		}


	};

} }