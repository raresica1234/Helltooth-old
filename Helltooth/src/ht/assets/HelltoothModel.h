#pragma once

#include "../graphics/rendering/model/RawModel.h"
#include "../tools/Cereal/Cereal.h"

#include "../utils/String.h"

namespace ht { namespace assets {
	

	class HelltoothModel {
	private:
		ht::graphics::RawModel* model = nullptr;

	public:
		HelltoothModel(ht::utils::String path);

		inline ht::graphics::RawModel* getRawModel() { return model; }

		static void StoreAsHelltoothModel(ht::utils::String path, ht::graphics::RawModel* model);
	};

} }