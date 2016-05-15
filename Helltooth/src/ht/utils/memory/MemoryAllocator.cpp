#include "MemoryAllocator.h"

namespace ht { namespace utils { 

	float MemoryAllocator::allocated;

	MemoryAllocator::MemoryAllocator() {
		allocated = 0;
	}


	void* MemoryAllocator::allocate(const int &size) {
		allocated += size / 1024.0f; //keep track of the allocated memory in KB
		int *memory = (int*) malloc(size + 4);
		*memory = size;
		memory += 1;
		std::cout << "Current memory allocated: " << allocated << " added " << size << std::endl;
		return (void*)memory;
	}

	void MemoryAllocator::deallocate(void *memory) {
		int *address = (int*)memory;
		address -= 1;
		int size = *address;
		allocated -= size / 1024.0f;
		free(address);
		std::cout << "Current memory allocated: " << allocated << " deleted " << size << std::endl;
	}

} }