#include "MemoryManager.h"


	void* operator new (std::size_t count) {
		return ht::utils::MemoryAllocator::allocate(count);
	}

	void* operator new[] (std::size_t count) {
		return ht::utils::MemoryAllocator::allocate(count);
	}

	void operator delete (void* ptr) {
		ht::utils::MemoryAllocator::deallocate(ptr);
	}

	void operator delete[](void* ptr) {
		ht::utils::MemoryAllocator::deallocate(ptr);
	}

	void operator delete  (void* ptr, const char *file, unsigned int line) {
		ht::utils::MemoryAllocator::deallocate(ptr);
		std::cout << "Deallocating memory in: " << file << ", at " << line << std::endl;
	}