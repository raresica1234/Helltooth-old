#pragma once

#include "../graphics/rendering/model/RawModel.h"

#include "../maths/maths.h"
#include "../maths/vec2.h"
#include "../maths/vec3.h"

#include <vector>

#include "../utils/Log.h"
#include "../utils/memory/MemoryManager.h"
#include "../utils/String.h"

namespace ht { namespace assets {

		class ObjLoader {
		public:
			static ht::graphics::RawModel* LoadObjFile(ht::utils::String& path);

		protected:
			static bool find(maths::vec3 pos, maths::vec3 normal, maths::vec2 uv, unsigned int *index,
				std::vector<maths::vec3> positions, std::vector<maths::vec3> normals, std::vector<maths::vec2> uvs) {
				bool find = false;
				for (*index = 0; *index < positions.size(); *index++) {
					if (pos == positions[*index]) {
						find = true;
						break;
					}
				}
				if (!find)
					return false;
				if (normal != normals[*index])
					return false;
				
				if (uv != uvs[*index])
					return false;

				return true;
			}
		};
} }