#pragma once

#include <GLFW/glfw3.h>

#include "RawModel.h"
#include "../Renderable.h"

#include "utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	struct Cube {
		//Position of the cube model, textures of the cube model
		f32 *data, *textureCoords;

		//Indices of the cube model
		uint32 *indices;


		//RawModel which contains all the data of the cube
		RawModel *model;

		//Default constructor.
		__forceinline Cube() {
			init();
			model = htnew RawModel(data, 3 * 4 * 6 * sizeof(f32));
			model->storeData(indices, 3 * 12 * sizeof(uint32));
			model->storeData(RAWMODEL_TEXTURE_COORDS, textureCoords, 2 * 4 * 6 * sizeof(f32));
		}

		//Return RawModel* of the cube.
		__forceinline RawModel* getModel() { return model; }

	protected:

		//this function sets all the data needed to make a cube
		//this function is hardcoded, later when i support obj models reading
		//i will have a special model loaded in Helltooth for this
		__forceinline void init() {
			this->data = htnew f32[3 * 4 * 6] {
				-1.0f,	1.0f, -1.0f,
				-1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f,	1.0f, -1.0f,

				-1.0f,  1.0f,  1.0f,
				-1.0f, -1.0f,  1.0f,
				 1.0f, -1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,

				 1.0f,  1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f,  1.0f,
				 1.0f,  1.0f,  1.0f,

				-1.0f,  1.0f, -1.0f,
				-1.0f, -1.0f, -1.0f,
				-1.0f, -1.0f,  1.0f,
				-1.0f,  1.0f,  1.0f,

				-1.0f,  1.0f,  1.0f,
				-1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f, -1.0f,
				 1.0f,  1.0f,  1.0f,

				-1.0f, -1.0f,  1.0f,
				-1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f, -1.0f,
				 1.0f, -1.0f,  1.0f
			};

			this->indices = htnew uint32[3 * 12] {
				 0,  1,  3,
				 3,  1,  2,
				 4,  5,  7,
				 7,  5,  6,
				 8,  9, 11,
				11,  9, 10,
				12, 13, 15,
				15, 13, 14,
				16, 17, 19,
				19, 17, 18,
				20, 21, 23,
				23, 21, 22
			};

			this->textureCoords = htnew f32[2 * 4 * 6]{
				0, 0,
				0, 1,
				1, 1,
				1, 0,
				0, 0,
				0, 1,
				1, 1,
				1, 0,
				0, 0,
				0, 1,
				1, 1,
				1, 0,
				0, 0,
				0, 1,
				1, 1,
				1, 0,
				0, 0,
				0, 1,
				1, 1,
				1, 0,
				0, 0,
				0, 1,
				1, 1,
				1, 0
			};
		}
	};

} }