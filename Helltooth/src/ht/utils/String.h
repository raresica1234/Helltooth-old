#pragma once

#include <iostream>
#include <vector>

#include "Log.h"

#include "utils/Internal.h"
#include "memory/MemoryManager.h"

namespace ht { namespace utils {

	class String {
		//TODO: Implement UTF-32 Characters!
	protected:
		char* data = nullptr;

		mutable uint32 hash_value = 0;

	public:
		uint32 size = 0;

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
		friend String operator+(String left, const String& right);
		friend String operator+(String left, const char* right);
		void operator+=(const String &other);
		void operator+=(const char &other);

		__forceinline void clear() {
			if (data)
				del[] data;
			data = htnew char[1];
			data[0] = 0;
			size = 1;
			hash_value = 0;
		}

		__forceinline void operator=(const String& other) {
			if (data != nullptr)
				del[] data;

			if (other.data == nullptr) {
				String();
				return;
			}
			size = strlen(other.data);
			data = htnew char[++size];
			memcpy(data, other.data, size);
			hash_value = 0;
		}

		__forceinline void operator=(const char* str) {
			if(data)
				del[] data;

			size = strlen(str) + 1;
			data = htnew char[size];
			memcpy(data, str, size);
			data[size - 1] = 0;
			hash_value = 0;
		}

		__forceinline void operator+=(char &other) { append(other); }
		__forceinline void operator+=(String &other) { append(other); }

		__forceinline char operator[](uint32 index) const {
			HT_ASSERT(index < size, "Index size %i bigger than string size %i!", index, size);
			return data[index];
		}

		__forceinline const char* c_str() const { return data; }

		__forceinline String substring(uint32 pos) const {
			char* a = htnew char[size - pos];
			memcpy(a, data + pos, size - pos);
			a[size - pos - 1] = 0;
			return String(a); 
		}

		__forceinline String cut(uint32 pos) const {
			char* a = htnew char[size - pos + 1];
			memcpy(a, data, size - pos);
			a[size - pos] = 0;
			return String(a);
		}

		unsigned int hash() const;
	};
} }


namespace std {
	template<>
	struct hash<ht::utils::String> {
		size_t operator()(const ht::utils::String &value) const {
			return value.hash();
		}
	};
}
