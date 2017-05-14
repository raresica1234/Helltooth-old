#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "String.h"

#include "memory/MemoryManager.h"

namespace ht { namespace utils {

	class FileUtils {
	public:
		static String read_file(const char* filepath) {
			FILE* file = fopen(filepath, "rt");
			if (!file) {
				HT_FATAL("[FILEUTILS] Cannot read %c", filepath);
				return nullptr;
			}
			fseek(file, 0, SEEK_END);
			uint32 length = ftell(file);
			char* data = htnew char[length + 1];
			memset(data, 0, length + 1);
			fseek(file, 0, SEEK_SET);
			fread(data, 1, length, file);
			fclose(file);
			String temp = data;
			del[] data;
			return temp;
		}

		static void write_file(const char* path, const void* data, const int32 dataSize) {
			FILE* file = fopen(path, "w");
			fwrite(data, 1, dataSize, file);
			fclose(file);
		}

		static String changeExtension(String path, String newExtension) {
			String result;

			std::vector<String> strings = path.split('.');
			if (strings.size() <= 2) {
				result = strings[0] + "." + newExtension;
			}
			else {
				String aux;
				for (uint32 i = 0; i < strings.size() - 1; i++)
					aux += strings[i];
				result = aux + "." + newExtension;
			}

			return result;
		}

	};

} }
