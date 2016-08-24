#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "memory/MemoryManager.h"


namespace ht { namespace utils {

	class FileUtils {
	public:
		static std::string read_file(const char* filepath) {
			FILE* file = fopen(filepath, "rt");
			if (!file) {
				HT_FATAL("[FILEUTILS] Cannot read %s", filepath);
				return nullptr;
			}
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

		static void write_file(const char* path, const void* data, const int dataSize) {
			FILE* file = fopen(path, "w");
			fwrite(data, 1, dataSize, file);
			fclose(file);
		}

		static std::string changeExtension(const char *file, std::string newExtension) {
			std::string sfile(file);
			int i = 0;
			for (i = sfile.size(); i > 0 ; i--) {
				if (sfile[i] == '.')
					break;
			}
			if (i == 0)
				HT_WARN("[FileUtils] Extension not found at file: %s", sfile);
			i++;
			std::string newFile;
			newFile = sfile.substr(0, i);
			newFile += newExtension;
			return newFile;
		}

	};

} }
