#pragma once

#include <iostream>

namespace ht { namespace utils { 

	class MemoryAllocator {
	private:
		static float allocated;
	public:
		MemoryAllocator();

		static void* allocate(const int &size);
		static void deallocate(void *memory);
	};

} }
