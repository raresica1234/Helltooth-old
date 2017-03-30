#include "HelltoothTexture.h"
#include "Asset.h"

namespace ht { namespace assets {

	using namespace utils;
	using namespace graphics;

	HelltoothTexture::HelltoothTexture(String filePath, unsigned int data) {
		Cereal::Buffer buffer = Cereal::Buffer(1);
		buffer.readFile(filePath.c_str());

		Cereal::Database* database = htnew Cereal::Database();
		database->read(buffer);

		Cereal::Object* object = database->getObject("texture");
		Cereal::Field* field = object->getField("width");
		int width = field->getValue<int>();
		int height = object->getField("height")->getValue<int>();
		byte bpp = object->getField("bpp")->getValue<byte>();

		Cereal::Array* pixels = object->getArray("pixels");

		if (texture) del texture;

		byte* pdata = pixels->getRawArray<byte>(new byte[pixels->getCount()]);
		if (data != 1) {
			texture = htnew Texture();
			texture->loadPixelArray(pdata, width, height, bpp);
		}
		else {
			this->data = htnew TextureData();
			this->data->pixels = htnew BYTE[pixels->getCount()];
			memcpy(this->data->pixels, pdata, pixels->getCount());
			this->data->width = (unsigned int)width;
			this->data->height = (unsigned int)height;
			this->data->bpp = bpp;
		}

		del[] pdata;

		del database;
	}

	void HelltoothTexture::StoreAsHelltoothTexture(String filePath, byte* pixels, int width, int height, byte bpp, size_t dataSize) {
		Cereal::Field* field1 = htnew Cereal::Field("width", width);
		Cereal::Field* field2 = htnew Cereal::Field("height", height);
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
		buffer.writeFile(filePath.c_str());
		del database;
	}

} }