#include "Manager.h"

namespace ht { namespace utils {

	Map<String, List<String>> VFS::mountPoints;


	void VFS::mount(const String& virtualPath, const String& physicalPath) {
		String path = const_cast<String&>(physicalPath);
		if (mountPoints.find(virtualPath) != List<String>())
			mountPoints[virtualPath].push(path);
		else {
			List<String> paths;
			paths.push(path);
			mountPoints.push(virtualPath, paths);
		}
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
		Strings dividedPath = newPath.split('/');
		if (mountPoints[dividedPath[0]].empty() || mountPoints.find(dividedPath[0]) == mountPoints.end())
			return false;

		String physicalPart;
		for (int i = 1; i < dividedPath.size; i++) {
			physicalPart += '/';
			physicalPart += dividedPath[i];
		}
		
		for (int i = 0; i < mountPoints[dividedPath[0]].size;i ++) {
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
