#pragma once

#include <array>
#include <unordered_map>

typedef char byte;

#define HT_SERIALIZATION_VERSION (short) 0x0100;
namespace ht { namespace tools { namespace serialization {

	class SerializationWriter {
	public:
		typedef char byte;

		static byte* header;
		static short version;
		
		template<typename T> int writeBytes(char* buffer, int position, const T& value);

	protected:
		 template<typename T> std::array<byte, sizeof(T)> static toBytes(const T& object);
	
	};

} } }
