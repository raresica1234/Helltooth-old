#include "Manager.h"

namespace ht { namespace utils {

	std::unordered_map<std::string, std::vector<std::string>> VFS::mountPoints;


	void VFS::mount(const std::string& virtualPath, const std::string& physicalPath) {
		mountPoints[virtualPath].push_back(physicalPath);
	}

	void VFS::unmount(const std::string& path) {
		mountPoints[path].clear();
	}

	bool VFS::resolvePhysicalPath(const std::string& path, std::string& outPhysicalPath) {
		if (path[0] != '/')
		{
			outPhysicalPath = path;
			return VFS::exists(path);
		}

		std::string newPath = path.substr(1);
		std::vector<std::string> dividedPath;
		split(newPath, '/', dividedPath);
		if (mountPoints.find(dividedPath[0]) == mountPoints.end() || mountPoints[dividedPath[0]].empty())
			return false;

		std::string physicalPart;
		for (int i = 1; i < dividedPath.size(); i++) 
			physicalPart +=  '/' + dividedPath[i];
		
		for (auto physicalPath : mountPoints[dividedPath[0]]) {
			std::string path = physicalPath + physicalPart;
			if (VFS::exists(path)) {
				outPhysicalPath = path;
				return true;
			}

		}

		return false;
	}

} }
