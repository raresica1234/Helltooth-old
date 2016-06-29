#pragma once

#include "MemoryAllocator.h"

#include "../Log.h"
#define h
#ifndef htnew
#define htnew	new(__FILE__, __LINE__)
#endif
#define MB 1024 * 1024
#if 0
#define htnew	new(__FILE__, __LINE__)

#define MB 1024 * 1024

inline void* operator new(size_t count) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		HT_WARN("Large allocation, size: %.2f MB", size);
	}
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void* operator new[](size_t count) noexcept {
	if (count > MB) {
		float size = (float) count / (MB);
		HT_WARN("Large allocation, size: %.2f MB", size);
	}
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void* operator new(size_t count, const char* file, unsigned int line) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		HT_WARN("Large allocation, size: %.2f MB", size);
	}
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void* operator new[](size_t count, const char* file, unsigned int line) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		HT_WARN("Large allocation, size: %.2f MB", size);
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
#endif