#pragma once

#include "Writer.h"
#include "Types.h"

#include <string>
#include <assert.h>

#include <iostream>

namespace ht { namespace tools { namespace serialization {

	class Array {

	private:
		Container container;
		byte type;
		unsigned short dataSize;
		byte* data;

	public:
		Array(std::string name, byte* data, short length) { setData(name, data, length,(byte)SERIALIZATION_BYTE); }
		Array(std::string name, bool* data, short length) { setData(name, data, length, (byte)SERIALIZATION_BOOL); }
		Array(std::string name, short* data, short length) { setData(name, data, length, (byte)SERIALIZATION_SHORT); }
		Array(std::string name, int* data, short length) { setData(name, data, length, (byte)SERIALIZATION_INT); }
		Array(std::string name, float* data, short length) { setData(name, data, length, (byte)SERIALIZATION_FLOAT); }
		Array(std::string name, long long* data, short length) { setData(name, data, length, (byte)SERIALIZATION_LONG); }
		Array(std::string name, double*data, short length) { setData(name, data, length, (byte)SERIALIZATION_DOUBLE); }

		int writeBytes(byte* dest, int pointer) {
			pointer = container.writeBytes(dest, pointer);
			pointer = SerializationWriter::writeBytes(dest, pointer, type);
			pointer = SerializationWriter::writeBytes(dest, pointer, dataSize);
			for (short i = 0; i < dataSize * Types::getSize(type); i++) {
				pointer = SerializationWriter::writeBytes(dest, pointer, data[i]);
			}
			return pointer;
		}

		~Array() {
			delete[] data;
		}

		static Array readBytes(byte* dest, int pointer) {
			short dataSize = SerializationWriter::readBytes<short>(dest, pointer += 2);
			if (SerializationWriter::readBytes<byte>(dest, pointer) != SERIALIZATION_ARRAY) assert(false);
			std::string name;
			pointer += 1;
			name = SerializationWriter::readBytes<std::string>(dest, pointer);
			pointer += 2 + name.length(); // sizeof short + name length
			byte type = SerializationWriter::readBytes<byte>(dest, pointer);
			pointer++;
			short dataCount = SerializationWriter::readBytes<short>(dest, pointer);
			pointer += 2;

			switch (type) {
			case SERIALIZATION_BYTE:
				{
					byte* arrayDatab = readArray<byte>(dest, dataCount, pointer);
					return Array(name, arrayDatab, dataCount);
				}
			case SERIALIZATION_BOOL:
				{
					bool* arrayDatabb = readArray<bool>(dest, dataCount, pointer);
					return Array(name, arrayDatabb, dataCount);
				}
			case SERIALIZATION_SHORT:
				{
					short* arrayDatas = readArray<short>(dest, dataCount, pointer);
					return Array(name, arrayDatas, dataCount);
				}
			case SERIALIZATION_INT:
				{
					int* arrayDatai = readArray<int>(dest, dataCount, pointer);
					return Array(name, arrayDatai, dataCount);
				}
			case SERIALIZATION_FLOAT:
				{
					float* arrayDataf = readArray<float>(dest, dataCount, pointer);
					return Array(name, arrayDataf, dataCount);
				}
			case SERIALIZATION_LONG:
				{
					long long* arrayDatal = readArray<long long>(dest, dataCount, pointer);
					return Array(name, arrayDatal, dataCount);
				}
			case SERIALIZATION_DOUBLE:
				{
					double* arrayDatad = readArray<double>(dest, dataCount, pointer);
					return Array(name, arrayDatad, dataCount);
				}
			}
			assert(false);
			return Array("", new byte[0], 0);
		}

		template<typename T>
		T* getArray() {
			assert(sizeof(T) == Types::getSize(type));
			T* result = new T[dataSize];

			for (int i = 0; i < dataSize; i++) {
				result[i] = SerializationWriter::readBytes<T>(data, i * sizeof(T));
			}

			return result;
		}

		inline short getDataSize() { return container.dataSize; }

	private:
		template<typename T>
		static T* readArray(byte* src, short size, int pointer) {
			T* data = new T[size];
			for (short i = 0; i < size; i++) {
				data[i] = SerializationWriter::readBytes<T>(src, pointer + (i * sizeof(T)));
			}
			return data;
		}
		
		template<typename T>
		void setData(std::string name, T* data, unsigned short length, byte type) {
			container.setType(SERIALIZATION_ARRAY);
			container.setName(name);
			int pointer = 0;
			this->type = type;
			dataSize = length;
			container.dataSize += sizeof(T) * length + 1 + 2;
			this->data = new byte[dataSize * sizeof(T)];
			for (unsigned short i = 0; i < dataSize; i++) {
				pointer = SerializationWriter::writeBytes(this->data, pointer, data[i]);
			}
		}
	};

} } }