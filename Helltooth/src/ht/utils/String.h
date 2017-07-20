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
		__forceinline ~String() {
			if (data) del[] data;
		}

		void operator=(const String& other);
		void operator=(const char* str);

		void append(const char* str);
		void append(const String &other);
		void append(const char str);

		bool operator!=(const String& other);
		bool operator==(const String& other) const;

		__forceinline friend String operator+(String left, const String& right) { left.append(right); return left; }
		__forceinline friend String operator+(String left, const char* right) { left.append(right); return left; }

		__forceinline void operator+=(char &other) { append(other); }
		__forceinline void operator+=(String &other) { append(other); }

		__forceinline void operator+=(const String &other) { append(other); }
		__forceinline void operator+=(const char &other) { append(other); }

		String operator--(int shit);

		std::vector<String> split(const char delimiter) const;

		String substring(uint32 pos) const;

		String cut(uint32 pos) const;
		
		unsigned int hash() const;

		__forceinline char operator[](uint32 index) const { HT_ASSERT(index < size, "Index size %i bigger than string size %i!", index, size); return data[index]; }
		__forceinline const char* c_str() const { return data; }
		
		__forceinline void clear() {
			if (data) del[] data;
			data = htnew char[1]; data[0] = 0;
			size = 1; hash_value = 0;
		}
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
