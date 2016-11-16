#pragma once

#include "List.h"

namespace ht { namespace utils {

	template<typename K, typename V>
	class Map {
	private:
		List<K> keys;
		List<V> values;

	public:
		Map() {}
		
		void push(K key, V value) {
			keys.push(key);
			values.push(value);
		}

		V find(K key) {
			unsigned int id = keys.find(key);
			if (id == -1)
				return V();
			return values[id];
		}

		Pair<K, V> find(unsigned int index) {
			return Pair<K, V>(keys[index], values[index]);
		}

		V operator[](K key) {
			return find(key);
		}

		void clear() {
			keys.clear();
			values.clear();
		}

		V end() {
			return values[values.size - 1];
		}

		bool empty() const {
			if (values.size > 0)
				return false;
			return true;
		}

		unsigned int size() {
			return keys.size;
		}
	};


} }
