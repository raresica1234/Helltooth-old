#pragma once

#include <vector>
#include <unordered_map>
#include <sstream>
#include <string>
namespace ht { namespace utils {

	class VFS {
	private:
		static std::unordered_map<std::string, std::vector<std::string>> mountPoints;


	public:
		
		static void mount(const std::string& virtualPath, const std::string& physicalPath);
		static void unmount(const std::string& path);

		static bool resolvePhysicalPath(const std::string& path, std::string& outPhysicalPath);

	private:
		inline static bool exists(std::string path) {
			struct stat buffer;
			return (stat(path.c_str(), &buffer) == 0);
		}
		
		inline static void split(const std::string &s, char delim, std::vector<std::string> &elems) {
			std::stringstream ss;
			ss.str(s);
			std::string item;
			while (std::getline(ss, item, delim)) {
				elems.push_back(item);
			}
		}
	};



} }

