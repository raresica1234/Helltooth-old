#pragma once

namespace ht { namespace utils {

	template<typename K, typename V>
	struct Pair {
		K key;
		V value;

		Pair(K key, V value) {
			this->key = key;
			this->value = value;
		}
	};

} }
