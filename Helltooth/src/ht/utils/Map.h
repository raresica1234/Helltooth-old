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
				return nullptr;
			return values[id];
		}

		V operator[](K key) {
			return find(key);
		}

	};


} }
