#include "String.h"

namespace ht { namespace utils {

	String::String(const char* str) {
		while (str[size] != '\0')
			size++;
		data = htnew char[++size];
		memcpy(data, str, size);
	}


	void String::append(const char* str) {
		unsigned int strlen = 0;
		while (str[strlen++] != '\0')
			;
		char* temp = htnew char[size + strlen - 1];
		memcpy(temp, data, size - 1);
		memcpy(temp + (size - 1), str, strlen);
		delete[] data;
		size = size + strlen - 1;
		data = htnew char[size];
		memcpy(data, temp, size);
		delete[] temp;
	}
	
	void String::append(const char str) {
		char* temp = htnew char[size + 1];
		memcpy(temp, data, size - 1);
		memcpy(temp + (size - 1), &str, 1);
		temp[size] = 0;
		size++;
		delete[] data;
		data = htnew char[size];
		memcpy(data, temp, size);
		delete[] temp;
	}

	void String::append(const String &other) {
		unsigned int strlen = other.size;
		char* temp = htnew char[size + strlen - 1];
		memcpy(temp, data, size - 1);
		memcpy(temp + (size - 1), other.data, strlen);
		delete[] data;
		size = size + strlen - 1;
		data = htnew char[size];
		memcpy(data, temp, size);
		delete[] temp;
	}

	bool String::operator!=(const String& other) const {
		if (size != other.size)
			return true;
		for (int i = 0; i < size; i++)
			if (data[i] != other[i])
				return true;
		return false;
	}

	bool String::operator==(const String& other) const {
		if (size != other.size)
			return false;
		bool result = true;
		for (int i = 0; i < other.size; i++)
			if (data[i] != other[i])
				result = false;
		return result;
	}

	String String::operator+(const String& other){
		append(other);
		return *this;
	}
	
	void String::operator+=(const String &other){
		append(other);
	}

	void String::operator+=(const char &other) {
		append(other);
	}

	List<String> String::split(const char delimiter) const {
		List<String> strings;
		String split = "";
		for (int i = 0; i < size; i++) {
			if (data[i] == delimiter) {
				strings.push(split);
				split = "";
			}
			split += data[i];
		}
		strings.push(split);
		return strings;
	}


} }

