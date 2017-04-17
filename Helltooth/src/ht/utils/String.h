#pragma once

#include <iostream>
#include <vector>

#include "Log.h"

#include "memory/MemoryManager.h"

namespace ht { namespace utils {

	class String {
		//TODO: Implement UTF-32 Characters!
	protected:
		char* data = nullptr;

	public:
		unsigned int size = 0;

	public:
		String() { data = htnew char[1];  data[0] = 0; size = 1; }
		String(const char* str);
		String(const String& other);

		void append(const char* str);
		void append(const String &other);
		void append(const char str);
		std::vector<String> split(const char delimiter) const;

		bool operator!=(const String& other);
		bool operator==(const String& other) const;
		friend String operator+(String& left, const String& right);
		void operator+=(const String &other);
		void operator+=(const char &other);

		__forceinline void clear() {
			if (data)
				del[] data;
			data = htnew char[1];
			data[0] = 0;
			size = 1;
		}

		__forceinline void operator=(const String& other) {
			if (data != nullptr)
				del[] data;

			if (other.data == nullptr) {
				String();
				return;
			}
			while (other.data[size] != '\0')
				size++;
			data = htnew char[++size];
			memcpy(data, other.data, size);
		}

		__forceinline void operator=(const char* str) {
			if(data)
				del[] data;

			size = strlen(str) + 1;
			data = htnew char[size];
			memcpy(data, str, size);
			data[size - 1] = 0;
		}

		__forceinline void operator+=(char &other) { append(other); }
		__forceinline void operator+=(String &other) { append(other); }

		__forceinline char operator[](unsigned int index) const {
			HT_ASSERT(index < size, "Index size %i bigger than string size %i!", index, size);
			return data[index];
		}

		__forceinline const char* c_str() const { return data; }

		__forceinline String substring(unsigned int pos) const { 
			char* a = htnew char[size - pos];
			memcpy(a, data + pos, size - pos);
			return String(a); 
		}
	};
} }

#define STRING_HASH_A 54059
#define STRING_HASH_B 76963
#define STRING_HASH_C 86969
#define STRING_HASH_FIRSTH 37

namespace std {
	template<>
	struct hash<ht::utils::String> {
		size_t operator()(const ht::utils::String &value) const {
			unsigned h = STRING_HASH_FIRSTH;
			for (unsigned int i = 0; i < value.size; i++) {
				h = (h * STRING_HASH_A) ^ (value[i] * STRING_HASH_B);
			}
			return h % STRING_HASH_C; // or return h % C;
		}
	};
}
