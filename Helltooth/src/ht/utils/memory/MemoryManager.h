#pragma once

#include "MemoryAllocator.h"

#define htnew	new(__FILE__,__LINE__)

inline void* operator new(std::size_t count) noexcept
{
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void* operator new[](std::size_t count) noexcept
{
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void* operator new(std::size_t count, const char* file, unsigned int line) noexcept
{
	// do whatever you want with file and line (hint: look for big allocations)
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void* operator new[](std::size_t count, const char* file, unsigned int line) noexcept
{
	// do whatever you want with file and line (hint: look for big allocations)
	return ht::utils::MemoryAllocator::allocate(count);
}

inline void operator delete(void* ptr) noexcept
{
	ht::utils::MemoryAllocator::deallocate(ptr);
}

inline void operator delete[](void* ptr) noexcept
{
	ht::utils::MemoryAllocator::deallocate(ptr);
}