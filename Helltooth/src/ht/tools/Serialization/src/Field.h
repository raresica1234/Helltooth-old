#pragma once

#include "Writer.h"
#include "Types.h"

namespace ht { namespace tools { namespace serialization {


	class Field {
	private:
		Container container;
		byte dataType;
		byte* data;
	
	public:
		
		inline Field(std::string name, byte value) {
			setData(value, name, SERIALIZATION_BYTE);
		}

		inline Field(std::string name, bool value) {
			setData(value, name, SERIALIZATION_BOOL);
		}

		inline Field(std::string name,short value) {
			setData(value, name, SERIALIZATION_SHORT);
		}

		inline Field(std::string name, int value) {
			setData(value, name, SERIALIZATION_INT);
		}

		inline Field(std::string name, float value) {
			setData(value, name, SERIALIZATION_FLOAT);
		}

		inline Field(std::string name, long long value ) {
			setData(value, name, SERIALIZATION_LONG);
		}

		inline Field(std::string name, double value) {
			setData(value, name, SERIALIZATION_DOUBLE);
		}

		inline ~Field() {
			delete[] data;
		}

		inline int writeBytes(byte* dest, int pointer) {
			pointer = container.writeBytes(dest, pointer);
			pointer = SerializationWriter::writeBytes(dest, pointer, dataType);
			for (int i = 0; i < Types::getSize(dataType); i++) {
				pointer = SerializationWriter::writeBytes(dest, pointer, data[i]);
			}
			return pointer;
		}

		inline static Field readBytes(byte* dest, int pointer) {
			short dataSize = SerializationWriter::readBytes<short>(dest, pointer+=2);
			if (SerializationWriter::readBytes<byte>(dest, pointer) != SERIALIZATION_FIELD) assert(false);
			pointer += 1;
			std::string name = SerializationWriter::readBytes<std::string>(dest, pointer);
			pointer += name.length() + 2;
			byte type = SerializationWriter::readBytes<byte>(dest, pointer);
			pointer++;
			switch (type) {
			case SERIALIZATION_BYTE:
				return Field(name,SerializationWriter::readBytes<byte>(dest, pointer));
			case SERIALIZATION_BOOL:
				return Field(name, SerializationWriter::readBytes<byte>(dest, pointer));
			case SERIALIZATION_SHORT:
				return Field(name, SerializationWriter::readBytes<short>(dest, pointer));
			case SERIALIZATION_INT:
				return Field(name, SerializationWriter::readBytes<int>(dest, pointer));
			case SERIALIZATION_FLOAT:
				return Field(name, SerializationWriter::readBytes<float>(dest, pointer));
			case SERIALIZATION_LONG:
				return Field(name, SerializationWriter::readBytes<long long>(dest, pointer));
			case SERIALIZATION_DOUBLE:
				return Field(name, SerializationWriter::readBytes<double>(dest, pointer));
			}
			assert(false);
			return Field("", 1);
		}

		template<typename T>
		T getValue() {
			return SerializationWriter::readBytes<T>(data, 0);
		}

		bool checkData(short dataSize) { return container.dataSize == dataSize; }

		inline short getDataSize() { return container.dataSize; }

	private:
		template<class T>
		void setData(T value, std::string name, byte dataType) {
			this->dataType = dataType;
			container.setType(SERIALIZATION_FIELD);
			container.setName(name);
			data = new byte[sizeof(T)];
			SerializationWriter::writeBytes(data, 0, value);
			container.dataSize += Types::getSize(dataType) + 1;
		}
	
	};


} } }
