#pragma once

#include <iostream>

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

		void push(T& element) {
			reserve();
			data[size++] = element;
		}

		void fit() {
			if (size == reserve)
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

		T& operator[](unsigned int index) const {
			HT_ASSERT(size >= index, "Index %i bigger than list size %i!", index, size);
			return data[index];
		}
	};


} }
