#include "MemoryAllocator.h"
#include "../Log.h"

namespace ht { namespace utils {

	f32 MemoryAllocator::allocated;
	bool MemoryAllocator::initialized = false;

	static_assert(sizeof(byte) == 1, "Invalid size of byte!");

	void* MemoryAllocator::allocate(uint32 size) {
		if (!initialized) { start(); initialized = true; }

		allocated += size; //keep track of the allocated memory in KB

		byte* memory = (byte*) malloc(size + sizeof(uint32));
		uint32* addr = (size_t*)memory;
		*addr = size;
		//*(size_t*)memory = size;
		memory += sizeof(size_t);

		return (void*)memory;
	}

	void MemoryAllocator::deallocate(void *memory) {
		if (!initialized) { start(); initialized = true; }

		if (memory == nullptr) {
			// the pointer is null
			__debugbreak();
		}

		byte* address = (byte*)memory;
		address -= sizeof(uint32);
		uint32 size = *(uint32*)address;
		free(address);

		allocated -= size;
	}

} }