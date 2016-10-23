#pragma once

#include <iostream>
#include <vector>

#include "../graphics/textures/Texture.h"

#include "../utils/memory/MemoryManager.h"

#include "../tools/Cereal/Cereal.h"

namespace ht { namespace assets {

	using namespace graphics;

	class HelltoothTexture {
	private:
		Texture* texture = nullptr;

	public:
		HelltoothTexture(const char* filePath) {
			Cereal::Buffer buffer = Cereal::Buffer(1);
			buffer.readFile(filePath);

			Cereal::Database* database = htnew Cereal::Database();
			database->read(buffer);

			Cereal::Object* object = database->getObject("texture");
			Cereal::Field* field = object->getField("width");
			int width = field->getValue<int>();
			int height = object->getField("height")->getValue<int>();
			byte bpp = object->getField("bpp")->getValue<byte>();

			Cereal::Array* pixels = object->getArray("pixels");

			if (texture) del texture;

			byte* data = pixels->getRawArray<byte>(new byte[pixels->getCount()]);

			texture = htnew Texture();
			texture->loadPixelArray(data, width, height, bpp);

			del[] data;

			del database;
		}

		inline Texture* getTexture() {
			return texture;
		}
		

		inline static void storeAsHelltoothTexture(const char* filePath, byte* pixels, int width, int height, byte bpp, size_t dataSize) {
			Cereal::Field* field1 = htnew Cereal::Field("width", width);
			Cereal::Field* field2 = htnew Cereal::Field("height", width);
			Cereal::Field* field3 = htnew Cereal::Field("bpp", bpp);
			
			Cereal::Array* array = htnew Cereal::Array("pixels", pixels, dataSize);
			
			Cereal::Object* object = htnew Cereal::Object("texture");
			
			object->addField(field1);
			object->addField(field2);
			object->addField(field3);
			object->addArray(array);

			Cereal::Database* database = htnew Cereal::Database("texture");
			database->addObject(object);

			Cereal::Buffer buffer = Cereal::Buffer(database->getSize());
			database->write(buffer);
			buffer.writeFile(filePath);
			delete database;
		}

	};

} }