#include "ResourceManager.h"

namespace ht { namespace assets {

	ResourceManager* ResourceManager::instance = nullptr;

	ResourceManager::~ResourceManager() {
		for (ResourceStack* stack : stacks)
			del stack;
	}

	bool ResourceManager::isAllLoaded() {
		bool loaded = true;
		for (ResourceStack* stack : stacks)
			loaded = loaded == false ? false : loaded && stack->isLoaded();
		return loaded;
	}

} }