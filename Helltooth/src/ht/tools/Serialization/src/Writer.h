#pragma once

#include <array>
#include <string>

#include <assert.h>

#include "../../../utils/memory/MemoryManager.h"

#define HT_SERIALIZATION_VERSION (short) 0x0100;
namespace ht { namespace tools { namespace serialization {

	typedef unsigned char byte;

	class SerializationWriter {
	public:

		static char* header;
		static short version;
		
		static int writeBytes(byte* dest, int pointer, std::string string);


		template<typename T>
		static T readBytes(byte* src, int pointer) {
			T value = src[pointer] << (sizeof(T) * 8 - 8);
			for (int i = 0; i < (int) sizeof(T); i++) {
				value |= (src[pointer + i] << ((sizeof(T) * 8 - 8) - (i * 8)));
			}
			return value;
		}

		template<>
		static float readBytes<float>(byte* src, int pointer) {
			unsigned int value = src[pointer] << (sizeof(int) * 8 - 8);
			for (int i = 0; i < (int) sizeof(float); i++) {
				value |= (src[pointer + i] << ((sizeof(int) * 8 - 8) - (i * 8)));
			}
			float result;
			memcpy_s(&result, 4, &value, 4);
			return result;
		}

		template<>
		static bool readBytes<bool>(byte* src, int pointer) {
			bool result;
			result = src[pointer];
			return result != 0;
		}

		template<>
		static double readBytes<double>(byte* src, int pointer) {
			unsigned long long value = src[pointer] << (sizeof(int) * 8 - 8);
			for (int i = pointer; i < (int)pointer + (int) sizeof(float); i++) {
				value |= (src[pointer + i] << ((sizeof(int) * 8 - 8) - (i * 8)));
			}
			double result;
			memcpy_s(&result, 4, &value, 4);
			return result;
		}

		template<>
		static std::string readBytes<std::string>(byte* src, int pointer) {
			char* value;
			short size = readBytes<short>(src, pointer);
			value = htnew char[size + 1];
			for (int i = pointer + 2; i < pointer + size + 2; i++) {
				value[i - pointer - 2] = readBytes<char>(src, i);
			}
			value[size] = 0; // null termination char, to be removed when i make my own class
			return std::string(value);
		}

		template<typename T>
		static int writeBytes(byte* dest, int pointer, const T& value) {
			auto asBytes = toBytes(value);
			for (byte c : asBytes) {
				dest[pointer++] = c;
			}
			return pointer;
		}

		template<>
		static int writeBytes(byte* dest, int pointer, const int& value) {
			dest[pointer++] = (byte)((value >> 24) & 0xff);
			dest[pointer++] = (byte)((value >> 16) & 0xff);
			dest[pointer++] = (byte)((value >> 8) & 0xff);
			dest[pointer++] = (byte)((value >> 0) & 0xff);
			return pointer;
		}

	protected:
		template<typename T>
		static std::array<byte, sizeof(T)> toBytes(const T& object) {
			std::array<byte, sizeof(T)> bytes;

			const byte* begin = reinterpret_cast<const byte*>(std::addressof(object));
			const byte* end = begin + sizeof(T);
			std::reverse_copy(begin, end, std::begin(bytes));

			return bytes;
		}
	
	};

	struct Container {
		byte type;
		std::string name;
		short dataSize;

		int writeBytes(byte* dest, int &pointer) {
			pointer = SerializationWriter::writeBytes(dest, pointer, dataSize);
			pointer = SerializationWriter::writeBytes(dest, pointer, type);
			pointer = SerializationWriter::writeBytes(dest, pointer, name);
			return pointer;
		}

		void setName(std::string name) {
			this->name = name;
			dataSize = 1 + name.length() + 2 + 2;
		}

		void setType(byte type) { this->type = type; }
	};

} } }