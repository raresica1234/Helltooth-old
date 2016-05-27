#pragma once

#include <GLFW/glfw3.h>
#include "../Renderable.h"
#include "RawModel.h"
#include "../../../utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	struct Cube {
		//Position of the cube model
		GLfloat *data;

		//Indices of the cube model
		GLuint *indices;

		//RawModel which contains all the data of the cube
		RawModel *model;


		//Default constructor.
		inline Cube() {
			init();
			model = htnew RawModel(data, 3 * 4 * 6 * sizeof(GLfloat));
			model->storeData(indices, 3 * 12 * sizeof(GLuint));
		}

		//Return RawModel* of the cube.
		inline RawModel* getModel() { return model; }

	protected:
		inline void init() {
			this->data = htnew GLfloat[3 * 4 * 6] {
				-0.5f,	0.5f, -0.5f,
				-0.5f, -0.5f, -0.5f,
				 0.5f, -0.5f, -0.5f,
				 0.5f,	0.5f, -0.5f,

				-0.5f,  0.5f,  0.5f,
				-0.5f, -0.5f,  0.5f,
				 0.5f, -0.5f,  0.5f,
				 0.5f,  0.5f,  0.5f,

				 0.5f,  0.5f, -0.5f,
				 0.5f, -0.5f, -0.5f,
				 0.5f, -0.5f,  0.5f,
				 0.5f,  0.5f,  0.5f,

				-0.5f,  0.5f, -0.5f,
				-0.5f, -0.5f, -0.5f,
				-0.5f, -0.5f,  0.5f,
				-0.5f,  0.5f,  0.5f,

				-0.5f,  0.5f,  0.5f,
				-0.5f,  0.5f, -0.5f,
				 0.5f,  0.5f, -0.5f,
				 0.5f,  0.5f,  0.5f,

				-0.5f, -0.5f,  0.5f,
				-0.5f, -0.5f, -0.5f,
				 0.5f, -0.5f, -0.5f,
				 0.5f, -0.5f,  0.5f
			};

			this->indices = htnew GLuint[3 * 12] {
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
		}

	public:
		inline ~Cube() {
			delete model;
		}
	};

} }