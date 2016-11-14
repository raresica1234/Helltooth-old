#include "String.h"

namespace ht { namespace utils {

	String::String(const char* str) {
		while (str[size] != '\0')
			size++;
		data = htnew char[size];
		memcpy(data, str, size);
	}


	void String::append(const char* str) {
		unsigned int strlen = 0;
		while (str[strlen] != '\0')
			strlen++;
		this->size += strlen;
		char* savedData = htnew char[size];
		memcpy(savedData, data, size - strlen);
		memcpy(savedData + size, str, strlen);
		delete[] data;
		data = htnew char[size];
		memcpy(data, savedData, size);
		delete[] savedData;
	}
	
	void String::append(const char str) {
		char* savedData = htnew char[++size];
		memcpy(savedData, data, size - 2);
		savedData[size - 1] = str;
		delete[] data;
		data = htnew char[size];
		memcpy(data, savedData, size);
		delete[] savedData;
	}


	void String::append(const String &other) {
		this->size += other.size;
		char* savedData = htnew char[size];
		memcpy(savedData, data, size - other.size);
		memcpy(savedData + size, other.data, other.size);
		delete[] data;
		data = htnew char[size];
		memcpy(data, savedData, size);
		delete[] savedData;
	}

	bool String::operator!=(const String& other) {
		if (size != other.size)
			return true;
		for (int i = 0; i < size; i++)
			if (data[i] != other[i])
				return true;
		return false;
	}

	bool String::operator==(const String& other) {
		if (size != other.size)
			return false;
		bool result = true;
		for (int i = 0; i < size; i++)
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

	List<String> String::split(const char delimiter) {
		List<String> strings;
		String split = "";
		for (int i = 0; i < size; i++) {
			if (data[i] == delimiter) {
				strings.push(split);
				split = "";
			}
			split += data[i];
		}
		return strings;
	}


} }

