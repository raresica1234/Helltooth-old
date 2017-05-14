#pragma once

#include "graphics/rendering/model/RawModel.h"
#include "tools/Cereal/Cereal.h"

#include "utils/Internal.h"
#include "utils/String.h"

namespace ht { namespace assets {

	class HelltoothModel {
	private:
		graphics::RawModel* model = nullptr;

	public:
		HelltoothModel(utils::String path);

		__forceinline graphics::RawModel* getRawModel() { return model; }

		static void StoreAsHelltoothModel(utils::String path, graphics::RawModel* model);
	};
} }