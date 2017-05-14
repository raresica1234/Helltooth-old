#include "Manager.h"

namespace ht { namespace utils {

	std::unordered_map<String, std::vector<String>> VFS::mountPoints;

	void VFS::mount(const String& virtualPath, const String& physicalPath) {
		String path = String();
		path = physicalPath;
		if (path[path.size - 2] != '/') {
			HT_WARN("[VFS] Path \"%s\" does not end in forward slash! Path will be adjusted!", physicalPath);
			path += "/";
		}
		mountPoints[virtualPath].push_back(path);
	}

	void VFS::unmount(const String& path) {
		mountPoints[path].clear();
	}

	bool VFS::resolvePhysicalPath(const String &path, String &outPhysicalPath) {
		if (path[0] != '/') {
			outPhysicalPath = path;
			return VFS::exists(path);
		}

		String newPath = path.substring(1);
		std::vector<String> dividedPath = newPath.split('/');
		if (mountPoints[dividedPath[0]].empty() || mountPoints.find(dividedPath[0]) == mountPoints.end())
			return false;

		String physicalPart;
		for (uint32 i = 1; i < dividedPath.size(); i++) {
			if(i > 1)
				physicalPart += '/';
			physicalPart += dividedPath[i];
		}
		
		for (uint32 i = 0; i < mountPoints[dividedPath[0]].size();i ++) {
			String physicalPath = mountPoints[dividedPath[0]][i];
			String path = physicalPath + physicalPart;
			if (VFS::exists(path)) {
				outPhysicalPath = path;
				return true;
			}
		}
		return false;
	}

} }
