#pragma once

#include <vector>
#include <string>

#include "Writer.h"
#include "Field.h"
#include "Array.h"
#include "Types.h"

namespace ht { namespace tools { namespace serialization{ 

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

		~Object() {
			//delete fields;
			//delete arrays;
		}

		inline void addField(Field &field) {
			fields.push_back(field);
		}

		inline void addArray(Array &array) {
			arrays.push_back(array);
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

		static Object readBytes(byte* dest, int pointer) {
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
				object.addField(field);
				currentPointer += field.getDataSize();
			}
			currentPointer += 2;

			while (SerializationWriter::readBytes<byte>(dest, currentPointer) == SERIALIZATION_ARRAY) {
				currentPointer -= 2;
				Array array = Array::readBytes(dest, currentPointer);
				object.addArray(array);
				currentPointer += array.getDataSize();
			}

			return object;
		}


	protected:
		inline void clean() {

		}
	};

} } }

