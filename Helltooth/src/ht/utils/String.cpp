#include "String.h"

namespace ht { namespace utils {

	String::String(const char* str) {
		if (str == nullptr) {
			String();
			return;
		}
		size = strlen(str) + 1;
		data = htnew char[size];
		memcpy(data, str, size);
		hash_value = 0;
	}

	String::String(const String& other) {
		if (data)
			del[] data;

		size = other.size;
		data = htnew char[size];
		memcpy(data, other.data, size);
		hash_value = 0;
	}


	void String::append(const char* str) {
		unsigned int strlen = 0;
		while (str[strlen++] != '\0')
			;
		char* temp = htnew char[size + strlen - 1];
		memcpy(temp, data, size - 1);
		memcpy(temp + (size - 1), str, strlen);
		del[] data;
		size = size + strlen - 1;
		data = htnew char[size];
		memcpy(data, temp, size);
		del[] temp;
		hash_value = 0;
	}
	
	void String::append(const char str) {
		char* temp = htnew char[size + 1];
		memcpy(temp, data, size - 1);
		memcpy(temp + (size - 1), &str, 1);
		temp[size] = 0;
		size++;
		del[] data;
		data = htnew char[size];
		memcpy(data, temp, size);
		del[] temp;
		hash_value = 0;
	}

	void String::append(const String &other) {
		unsigned int strlen = other.size;
		char* temp = htnew char[size + strlen - 1];
		memcpy(temp, data, size - 1);
		memcpy(temp + (size - 1), other.data, strlen);
		del[] data;
		size = size + strlen - 1;
		data = htnew char[size];
		memcpy(data, temp, size);
		del[] temp;
		hash_value = 0;
	}

	bool String::operator!=(const String& other) {
		if (size != other.size)
			return true;
		for (unsigned int i = 0; i < size; i++)
			if (data[i] == other[i])
				return false;
		return true;
	}

	bool String::operator==(const String& other) const {
		if (size != other.size)
			return false;
		
		for (unsigned int i = 0; i < size; i++) {
			if (data[i] != other.data[i])
				return false;
		}
		return true;
	}

	String operator+(String left, const String& right) {
		left.append(right);
		return left;
	}

	String operator+(String left, const char* right) {
		 left.append(right);
		 return left;
	}

	void String::operator+=(const String &other){
		append(other);
	}

	void String::operator+=(const char &other) {
		append(other);
	}

	std::vector<String> String::split(const char delimiter) const {
		std::vector<String> strings;
		String split = "";
		for (unsigned int i = 0; i < size - 1; i++) {
			if (data[i] == delimiter) {
				strings.push_back(split);
				split = "";
				continue;
			}
			split += data[i];
		}
		strings.push_back(split);
		return strings;
	}

	#define STRING_HASH_A 54059
	#define STRING_HASH_B 76963
	#define STRING_HASH_C 86969
	#define STRING_HASH_FIRSTH 37

	unsigned int String::hash() const {
		if (hash_value == 0) {
			unsigned h = STRING_HASH_FIRSTH;
			for (unsigned int i = 0; i < size; i++) {
				h = (h * STRING_HASH_A) ^ (data[i] * STRING_HASH_B);
			}

			hash_value = h % STRING_HASH_C;
		}
		return hash_value; // or return h % C;
	}
} }

