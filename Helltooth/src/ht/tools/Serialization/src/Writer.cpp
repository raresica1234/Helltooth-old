#include "Writer.h"

namespace ht { namespace tools { namespace serialization {

	char* SerializationWriter::header = "HT";
	short SerializationWriter::version = HT_SERIALIZATION_VERSION;

	
	int SerializationWriter::writeBytes(byte* dest, int pointer, std::string string) {
		const unsigned int size = (short)string.length();

		assert(size <= 65535);

		pointer = writeBytes(dest, pointer, (short)size);
		for (unsigned short i = 0; i < (short)size; i++) {
			pointer = writeBytes(dest, pointer, string[i]);
		}
		return pointer;
	}


} } }