#pragma once
#pragma warning(disable:4595)

#include "MemoryAllocator.h"

#include "utils/Log.h"
#include "utils/Internal.h"
#ifdef htnew
#	error htnew already defined.
#endif
#ifndef htnew
#	define htnew	new(__FILE__, __LINE__)
#endif

#ifdef del
#	undef del
#endif

#ifndef del
#	define del delete
#endif

#define MB 1024 * 1024

inline void* operator new(ht::uint32 count) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		HT_WARN("Large allocation, size: %.2f MB", size);
	}
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void* operator new[](ht::uint32 count) noexcept {
	if (count > MB) {
		float size = (float) count / (MB);
		HT_WARN("Large allocation, size: %.2f MB", size);
	}
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void* operator new(ht::uint32 count, const char* file, ht::uint32 line) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		HT_WARN("Large allocation, size: %.2f MB %s", size, file);
	}
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void* operator new[](ht::uint32 count, const char* file, ht::uint32 line) noexcept {
	if (count > MB) {
		float size = (float)count / (MB);
		HT_WARN("Large allocation, size: %.2f MB %s", size, file);
	}
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void operator delete(void* ptr) noexcept {
	ht::utils::MemoryAllocator::deallocate(ptr);
}

inline void operator delete[](void* ptr) noexcept {
	ht::utils::MemoryAllocator::deallocate(ptr);
}

inline void operator delete(void* ptr, const char* file, ht::uint32 line) noexcept {
	ht::utils::MemoryAllocator::deallocate(ptr);
}

inline void operator delete[](void* ptr, const char* file, ht::uint32 line) noexcept {
	ht::utils::MemoryAllocator::deallocate(ptr);
}