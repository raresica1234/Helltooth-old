#pragma once

#include "MemoryAllocator.h"

#define htnew new(__FILE__,__LINE__)
#define htdel delete __FILE__,__LINE__,

class MemoryManager {

public:
	MemoryManager();
	~MemoryManager();

	friend void* operator new (std::size_t count);
	friend void* operator new[] (std::size_t count);

	friend void operator delete  (void* ptr);
	friend void operator delete[](void* ptr);

	friend void operator delete  (void* ptr, const char *file, unsigned int line);
};
