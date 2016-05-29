#pragma once

#include <iostream>

#include "../graphics/textures/Texture.h"

#include "../utils/memory/MemoryManager.h"
#if 0
namespace ht { namespace assets {



	using namespace graphics;

	class HelltoothTexture {
	
	public:
		static Texture openTexture(char* file) {
			FILE* f = fopen(file, "rt");
			fseek(f, 0, SEEK_END);
			unsigned long length = ftell(f);
			char* data = htnew char[length + 1];
			memset(data, 0, length + 1);
			fseek(f, 0, SEEK_SET);
			fread(data, 1, length, f);
			fclose(f);
			std::string temp = data;
			
			int currentOffset = 1; // the # that declares the header makes 1

			int width;
			int height = 0;
			std::string current;
			if (temp.substr(currentOffset, 1) == "w") {
				currentOffset+=2;
				const char* data;
				current = temp.substr(currentOffset, 4);
				data = current.c_str();
				width = data[0] << 3 | data[1] << 2 | data[2] << 1 | data[3];
				std::cout << "width " << width << std::endl;
				currentOffset += 5; // end of line
			}
			if (readNext(temp, 1, currentOffset) == "h") {
				currentOffset+=2;
				const char* data;
				current = temp.substr(currentOffset, 4);
				data = current.c_str();
				std::cout << "height " << data << std::endl;
				currentOffset += 4;
			}

			Texture texture;
			return texture;
		}

	protected:
		static inline const char* readNext(std::string temp, const int numberOfBytes, int &pointer) {
			std::string current = temp.substr(pointer, numberOfBytes);
			const char* data = current.c_str();
			pointer += numberOfBytes;
			return data;
		}

	};

} }
#endif