#pragma once

#include <iostream>

namespace ht { namespace utils {

	class MemoryAllocator {
	private:
		static float allocated;
		static bool initialized;

	public:
		// MemoryAllocator(); -> You do not have to construct a static class

		static void start() { allocated = 0; }

		static void* allocate(size_t size);
		static void deallocate(void* memory);

		static float getAllocatedB() { return (allocated * 1024.0f); }
		static float getAllocatedKB() { return allocated; }
		static float getAllocatedMB() { return (allocated / 1024.0f); }
	};

} }