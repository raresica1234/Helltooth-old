#pragma once

#include <sstream>
#include <unordered_map>

#include "utils/String.h"

namespace ht { namespace utils {

	class VFS {
	private:
		static std::unordered_map<String, std::vector<String>> mountPoints;

	public:
		
		static void mount(const String& virtualPath, const String& physicalPath);
		static void unmount(const String& path);

		static bool resolvePhysicalPath(const String& path, String& outPhysicalPath);

	private:
		inline static bool exists(String path) {
			struct stat buffer;
			return (stat(path.c_str(), &buffer) == 0);
		}
	};

} }

