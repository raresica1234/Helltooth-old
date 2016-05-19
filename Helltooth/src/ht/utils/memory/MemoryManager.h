#pragma once

#include "MemoryAllocator.h"

#define htnew	new(__FILE__,__LINE__)

#define MB 1024 * 1024

inline void* operator new(std::size_t count) noexcept {
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void* operator new[](std::size_t count) noexcept {
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void* operator new(std::size_t count, const char* file, unsigned int line) noexcept {
	if (count > MB) {
		//LOG
		std::cout << "Large allocation: " << count / 1024.0f << " KB" << ", at FILE: " << file << " LINE: " << line << std::endl;
	}
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void* operator new[](std::size_t count, const char* file, unsigned int line) noexcept {
	if (count > MB) {
		//LOG
		std::cout << "Large allocation: " << count / 1024.0f << " KB" << ", at FILE: " << file << " LINE: " << line << std::endl;
	}
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void operator delete(void* ptr) noexcept {
	ht::utils::MemoryAllocator::deallocate(ptr);
}

inline void operator delete[](void* ptr) noexcept {
	ht::utils::MemoryAllocator::deallocate(ptr);
}

inline void operator delete(void* ptr, const char* file, unsigned int line) noexcept {
	ht::utils::MemoryAllocator::deallocate(ptr);
}

inline void operator delete[](void* ptr, const char* file, unsigned int line) noexcept {
	ht::utils::MemoryAllocator::deallocate(ptr);
}