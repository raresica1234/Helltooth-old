#pragma once

#include <vector>
#include <string>

#include "Writer.h"
#include "Field.h"
#include "Array.h"
#include "Types.h"

#include "../../../utils/memory/MemoryManager.h"

namespace ht { namespace tools { namespace serialization { 

	class Object {
	private:
		Container container;
		std::vector<Field> fields;
		std::vector<Array> arrays;

	public:
		inline Object(std::string name) {
			container.setName(name);
			container.setType(SERIALIZATION_OBJECT);
		}

		~Object() { }

		inline void addField(const Field* field) {
			fields.push_back(*field);
		}

		inline void addArray(const Array* array) {
			arrays.push_back(*array);
		}

		inline int writeBytes(byte* dest, int pointer) {
			pointer = container.writeBytes(dest, pointer);
			for (Field field : fields) {
				pointer = field.writeBytes(dest, pointer);
			}

			for (Array array : arrays) {
				pointer = array.writeBytes(dest, pointer);
			}
			return pointer;
		}

		inline static Object readBytes(byte* dest, int pointer) {
			int currentPointer = pointer;
			currentPointer += 2;
			byte type = SerializationWriter::readBytes<byte>(dest, currentPointer++);
			assert(type == SERIALIZATION_OBJECT);
			std::string name = SerializationWriter::readBytes<std::string>(dest, currentPointer);
			currentPointer += name.length() + 2;

			Object object(name);
			currentPointer += 2;
			while (SerializationWriter::readBytes<byte>(dest, currentPointer) == SERIALIZATION_FIELD) {
				currentPointer -= 2;
				Field field = Field::readBytes(dest, currentPointer);
				Field *field2;
				*field2 = field;
				object.addField(field2);
				delete field2;
				currentPointer += field.getDataSize();
			}
			currentPointer += 2;

			while (SerializationWriter::readBytes<byte>(dest, currentPointer) == SERIALIZATION_ARRAY) {
				currentPointer -= 2;
				Array array = Array::readBytes(dest, currentPointer);
				Array *array2;
				*array2 = array;
				object.addArray(array2);
				delete array2;
				currentPointer += array.getDataSize();
			}

			return object;
		}

		inline std::string getName() { return container.name; }

		inline Field findField(std::string name) {
			for (Field field : fields) {
				if (field.getName() == name) {
					return field;
				}
			}
			HT_FATAL("[SERIALIZATION] Field %s not found, object name %s", name, container.name);
			return Field("",-1);
		}

		inline Array findObject(std::string name) {
			for (Array array : arrays) {
				if (array.getName() == name) {
					return array;
				}
			}
			HT_FATAL("[SERIALIZATION] Field %s not found, object name %s", name, container.name);
			return Array("", new int[1]{ -1 }, 1);
		}


	protected:
		inline void clean() {

		}
	};

} } }

