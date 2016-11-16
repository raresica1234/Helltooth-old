#pragma once

#include "../graphics/rendering/model/RawModel.h"
#include "../tools/Cereal/Cereal.h"

#include "../utils/String.h"

namespace ht { namespace assets {
	
	using namespace graphics;
	using namespace utils;

	class HelltoothModel {
	private:
		RawModel* model = nullptr;

	public:
		HelltoothModel(String path);

		inline RawModel* getRawModel() { return model; }

		static void storeAsHelltoothModel(String path, RawModel* model);
	};

} }