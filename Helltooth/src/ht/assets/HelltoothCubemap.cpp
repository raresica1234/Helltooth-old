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
		cubemap->bpp = (unsigned int)object->getField("textureBpp")->getValue<int>();
		cubemap->width = (unsigned int)object->getField("textureWidth")->getValue<int>();
		cubemap->height = (unsigned int)object->getField("textureHeight")->getValue<int>();

		unsigned int size = cubemap->width * cubemap->height * cubemap->bpp / 8;
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