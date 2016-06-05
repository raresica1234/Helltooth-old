#pragma once

#include <array>
#include <string>

#include <assert.h>

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
			for (int i = pointer; i < pointer + sizeof(T); i++) {
				value |= src[pointer + i] << ((sizeof(T) * 8 - 8) - (i * 8));
			}
			return value;
		}

		template<>
		static std::string readBytes<std::string>(byte* src, int pointer) {
			char* value;
			short size = readBytes<short>(src, pointer);
			value = new char[size + 1];
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

} } }
