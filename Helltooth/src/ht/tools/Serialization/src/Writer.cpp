#include "Writer.h"

namespace ht { namespace tools { namespace serialization {

	byte* SerializationWriter::header = "HT";
	short SerializationWriter::version = HT_SERIALIZATION_VERSION;

	template<typename T> int SerializationWriter::writeBytes(char* buffer, int position, const T& value) {
		auto asBytes = to_bytes(value);
		for (byte c : asBytes) {
			buffer[position++] = c;
		}
		return position;
	}


	template<typename T> std::array<byte, sizeof(T)> static SerializationWriter::toBytes(const T& object) {
		std::array<byte, sizeof(T)> bytes;

		const byte* begin = reinterpret_cast<const byte*>(std::addressof(object));
		const byte* end = begin + sizeof(T);
		std::copy(begin, end, std::begin(bytes));

		return bytes;
	}

} } }