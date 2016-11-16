#pragma once

#include <sstream>

#include "../../../utils/List.h"
#include "../../../utils/String.h"
#include "../../../utils/Map.h"

namespace ht { namespace utils {

	class VFS {
	private:
		static Map<String, List<String>> mountPoints;


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

