#pragma once

#include <iostream>
#include "memory/MemoryManager.h"

#include "Log.h"
#include "List.h"

namespace ht { namespace utils {

	class String {
		//TODO: Implement UTF-32 Characters!
	protected:
		char* data = nullptr;

	public:
		unsigned int size = 0;

	public:
		String() { }
		String(const char* str);

		void append(const char* str);
		void append(const String &other);
		void append(const char str);
		List<String> split(const char delimiter);

		bool operator!=(const String& other);
		bool operator==(const String& other);
		String operator+(const String& other);
		void operator+=(const String &other);

		inline void operator=(const String& other) {
			if (data)
				delete[] data;

			data = htnew char[other.size];
			size = other.size;

			memcpy(data, other.data, size);
		}

		inline void operator=(const char* str) {
			if(data)
				delete[] data;

			size = 0;
			while (str[size] != '\0')
				size++;

			data = htnew char[size];
			memcpy(data, str, size);
		}

		__forceinline void operator+=(char &other) {
			append(other);
		}

		__forceinline char& operator[](unsigned int index) const {
			HT_ASSERT(index > size, "Index size %i bigger than string size %i!", index, size);
			return data[index];
		}
	};



} }
