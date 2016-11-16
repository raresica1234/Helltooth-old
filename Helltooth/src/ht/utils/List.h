#pragma once

#include <iostream>

#include "memory/MemoryManager.h"

#define Strings List<String>
#define Ints List<int>
#define Floats List<float>
#define UInts List<unsigned int>
#define Vec2s List<maths::vec2>
#define Vec3s List<maths::vec3>
#define Vec4s List<maths::vec4>

namespace ht { namespace utils {
	
	template<typename K, typename V>
	struct Pair {
		K key;
		V value;

		Pair() {}

		Pair(K key, V value) : key(key), value(value) {}
	};

	template<typename T>
	class List {
	private:
		T* data = nullptr;

		unsigned int reserved = 1;
		unsigned int extraReserve = 1;
	public:
		unsigned int size = 0;
	public:
		List() {
			data = htnew T[1];
		}

		List(const List<T>& other) {
			data = htnew T[other.reserved];
			size = other.size;
			reserved = other.reserved;
			extraReserve = extraReserve;
			memcpy(data, other.data, other.size * sizeof(T));
		}

		List(unsigned int reserved, unsigned int extraReserve = 1) {
			data = htnew T[reserved];
			this->reserved = reserved;
			this->extraReserve = extraReserve;
		}
		
		~List() {
			del[] data;
		}

		void reserve() {
			if (size < reserved)
				return;
			
			T* temp = htnew T[size];
			memcpy(temp, data, size * sizeof(T));
			del[] data;
			reserved += extraReserve;
			data = htnew T[reserved];
			memcpy(data, temp, size * sizeof(T));
			del[] temp;
		}

		void resize(unsigned int res) {
			this->reserved = res;
			T* temp = htnew T[size];
			memcpy(temp, data, size * sizeof(T));
			del[] data;
			reserved += extraReserve;
			data = htnew T[reserved];
			memcpy(data, temp, size * sizeof(T));
			del[] temp;
		}

		void push(T element) {
			reserve();
			data[size++] = element;
		}
		void fit() {
			if (size == reserved)
				return;
			T* temp = htnew T[size];
			memcpy(temp, data, size * sizeof(T));
			reserved = size;
			del[] data;
			data = htnew T[size];
			memcpy(data, temp, size * sizeof(T));
			del[] temp;
		}
		
		unsigned int find(T& element) {
			for (unsigned int i = 0; i < size; i++)
				if (data[i] == element)
					return i;
			return -1;
		}

		void clear() {
			size = 0;
			reserved = 1;
			delete[] data;
			data = htnew T[1];
		}

		bool empty() {
			if (size > 0)
				return false;
			return true;
		}

		T& operator[](unsigned int index) const {
			HT_ASSERT(size >= index, "Index %i bigger than list size %i!", index, size);
			return data[index];
		}

		bool operator==(List<T> &other) {
			if (size != other.size)
				return false;
			for (int i = 0; i < size; i++) 
				if (data[i] != other[i])
					return false;
			return true;
		}

		bool operator!=(List<T> &other) {
			if (size == 0)
				return false;
			if (size != other.size)
				return true;
			for (int i = 0; i < size; i++)
				if (data[i] == other[i])
					return false;
			return true;
		}
	};


} }
