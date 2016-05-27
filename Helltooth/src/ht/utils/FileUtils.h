#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../../ht/utils/memory/MemoryManager.h"

namespace ht { namespace utils {

	class FileUtils {
	public:
		static std::string read_file(const char* filepath) {
			FILE* file = fopen(filepath, "rt");
			fseek(file, 0, SEEK_END);
			unsigned long length = ftell(file);
			char* data = htnew char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);
			std::string temp = data;
			delete[] data;
			return temp;
		}

	};

} }
