#include "HelltoothCubemap.h"

namespace ht { namespace assets {
	using namespace utils;
	
	HelltoothCubemap::HelltoothCubemap(String path) {
		Cereal::Buffer buffer = Cereal::Buffer(1);
		buffer.readFile(path.c_str());

		Cereal::Database* database = htnew Cereal::Database();
		database->read(buffer);

		Cereal::Object* object = database->getObject("faces");

		cubemap = htnew Cubemap();
		cubemap->bpp = (uint32)object->getField("textureBpp")->getValue<int32>();
		cubemap->width = object->getField("textureWidth")->getValue<int32>();
		cubemap->height = object->getField("textureHeight")->getValue<int32>();

		uint32 size = (uint32)(cubemap->width * cubemap->height * (cubemap->bpp / 8));

		cubemap->left = htnew byte[size];
		cubemap->right = htnew byte[size];
		cubemap->top = htnew byte[size];
		cubemap->bottom = htnew byte[size];
		cubemap->back = htnew byte[size];
		cubemap->front = htnew byte[size];

		object->getArray("left")->getRawArray<Cereal::byte>(cubemap->left);
		object->getArray("right")->getRawArray<Cereal::byte>(cubemap->right);
		object->getArray("top")->getRawArray<Cereal::byte>(cubemap->top);
		object->getArray("bottom")->getRawArray<Cereal::byte>(cubemap->bottom);
		object->getArray("back")->getRawArray<Cereal::byte>(cubemap->back);
		object->getArray("front")->getRawArray<Cereal::byte>(cubemap->front);

		del database;
	}
} }