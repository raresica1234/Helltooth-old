#pragma once

#include <iostream>

#include "utils/Internal.h"

namespace ht { namespace utils {

	class MemoryAllocator {
	private:
		static f32 allocated;
		static bool initialized;

	public:
		// MemoryAllocator(); -> You do not have to construct a static class

		static void start() { allocated = 0; }

		static void* allocate(uint32 size);
		static void deallocate(void* memory);

		static float getAllocatedB() { return (allocated * 1024.0f); }
		static float getAllocatedKB() { return allocated; }
		static float getAllocatedMB() { return (allocated / 1024.0f); }
	};

} }