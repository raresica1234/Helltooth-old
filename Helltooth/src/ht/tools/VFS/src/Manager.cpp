#include "Manager.h"

namespace ht { namespace utils {

	std::unordered_map<String, std::vector<String>> VFS::mountPoints;


	void VFS::mount(const String& virtualPath, const String& physicalPath) {
		String path = String();
		if (physicalPath[physicalPath.size - 1] == '/') {
			HT_WARN("[VFS] Physical path ends in forward slash! Path will be adjusted.");
			for (unsigned int i = 0; i < physicalPath.size - 1; i++)
				path += physicalPath[i];
		}
		else path = const_cast<String&>(physicalPath);
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
		for (unsigned int i = 1; i < dividedPath.size(); i++) {
			physicalPart += '/';
			physicalPart += dividedPath[i];
		}
		
		for (unsigned int i = 0; i < mountPoints[dividedPath[0]].size();i ++) {
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
