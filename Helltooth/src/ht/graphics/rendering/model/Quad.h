#pragma once

#include <GLFW/glfw3.h>

#include "RawModel.h"
#include "../Renderable.h"

#include "utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	struct Quad {
		f32 *data, *textureCoords;

		//Indices of the cube model
		uint32 *indices;
		
		RawModel *model;

		__forceinline Quad() {
			init();
			model = htnew RawModel(data, 3 * 4 * sizeof(f32));
			model->storeData(indices, 3 * 12 * sizeof(uint32));
			model->storeData(RAWMODEL_TEXTURE_COORDS, textureCoords, 2 * 4 * 6 * sizeof(f32));
		}
		
		__forceinline RawModel* getModel() { return model; }

	protected:
		__forceinline void init() {
			data = htnew f32[4 * 3]{
				-1.0f, -1.0f, 0.5f,
				 1.0f, -1.0f, 0.5f,
				 1.0f,  1.0f, 0.5f,
				-1.0f,  1.0f, 0.5f
			};

			textureCoords = htnew f32[4 * 2]{
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 1.0f
			};

			indices = htnew uint32[6]{
				0,1,2,
				0,2,3
			};
		}

	};

} }