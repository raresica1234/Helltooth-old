#include "MemoryAllocator.h"
#include "../Log.h"
#if 0

namespace ht { namespace utils {

	float MemoryAllocator::allocated;
	bool MemoryAllocator::initialized = false;

	typedef unsigned char byte;

	static_assert(sizeof(byte) == 1, "Invalid size of byte!");

	void* MemoryAllocator::allocate(size_t size) {
		if (!initialized) { start(); initialized = true; }

		allocated += size; //keep track of the allocated memory in KB

		byte* memory = (byte*) malloc(size + sizeof(size_t));
		size_t* addr = (size_t*)memory;
		*addr = size;
		//*(size_t*)memory = size;
		memory += sizeof(size_t);

		HT_MSG("Current memory allocated: %i", allocated);

		return (void*)memory;
	}

	void MemoryAllocator::deallocate(void *memory) {
		if (!initialized) { start(); initialized = true; }

		if (memory == nullptr) {
			// the pointer is null
			__debugbreak();
		}

		byte* address = (byte*)memory;
		address -= sizeof(size_t);
		size_t size = *(size_t*)address;
		free(address);

		HT_MSG("Current memory allocated: %i", allocated);

		allocated -= size;
	}

} }
#endif