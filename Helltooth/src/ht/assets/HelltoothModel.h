#pragma once

#include "../graphics/rendering/model/RawModel.h"
#include "../tools/Cereal/Cereal.h"

namespace ht { namespace assets {
	
	using namespace graphics;

	class HelltoothModel {
	private:
		RawModel* model = nullptr;

	public:
		HelltoothModel(const char *path);

		inline RawModel* getRawModel() { return model; }

		static void storeAsHelltoothModel(const char *path, RawModel* model);
	};

} }