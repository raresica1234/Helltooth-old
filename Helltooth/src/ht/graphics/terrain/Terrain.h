#pragma once

#include "../rendering/model/RawModel.h"
#include "../../maths/vec3.h"
#include "../../maths/vec2.h"

#include <vector>
#include "../../assets/Asset.h"
namespace ht { namespace graphics {

#define CHUNK_SIZE 16
#define TERRAIN_CHUNK_SIZE 16

	class Terrain {
	private:
		RawModel* model;
		std::vector<Chunk> chunks;

	public:
		Terrain(maths::vec2 location, const char* heightMap) {

		}

	};

	struct Chunk {
		std::vector<maths::vec3> vectors;
	};

} }
