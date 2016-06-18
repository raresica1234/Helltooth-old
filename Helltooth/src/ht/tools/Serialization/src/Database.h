#pragma once

#include <vector>
#include <string>

#include "Object.h"
#include "Writer.h"
#include "Types.h"

namespace ht { namespace tools { namespace serialization { 

	class Database {
	private:
		Container container;
		std::vector<Object> objects;
	public:
		inline Database(std::string name) {
			container.setName(name);
			container.setType(SERIALIZATION_DATABASE);
			container.dataSize = 0;
		}

		inline void addObject(Object &object) {
			objects.push_back(object);
		}

		inline int writeBytes(byte* dest, int pointer) {
			pointer = container.writeBytes(dest, pointer);
			if(!objects.empty())
				for (Object object : objects) {
					pointer = object.writeBytes(dest, pointer);
				}
			return pointer;
		}

		inline static Database readBytes(byte* dest, int pointer) {
			assert(SerializationWriter::readBytes<byte>(dest, pointer++) == SERIALIZATION_DATABASE);
			std::string name = SerializationWriter::readBytes<std::string>(dest, pointer);
			Database database(name);
			pointer += name.length() + 2;
			while (SerializationWriter::readBytes<byte>(dest, pointer) == SERIALIZATION_OBJECT) {
				Object object = Object::readBytes(dest, pointer);
				database.addObject(object);
			}

		}

		inline Object& findObject(std::string name) {
			for (Object object : objects) {
				if (object.getName() == name) {
					return object;
				}
			}
			HT_FATAL("[SERIALIZATION] Object %s not found, database name %s", name, container.name);
			assert(false);
			return Object("fail");
		}

	};

} } }
