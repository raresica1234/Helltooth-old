#pragma once

#include <GLFW/glfw3.h>
#include "../Renderable.h"
#include "RawModel.h"
#include "../../../utils/memory/MemoryManager.h" // include this file in all the files that use "new" or "delete"
#include "../BatchRenderer.h"

namespace ht { namespace graphics {

	struct Cube {
		GLfloat *data;
		GLuint *indices;
		RawModel *model;

		inline Cube() {
			init();
			model = htnew RawModel(data, 3 * 4 * 6 * sizeof(GLfloat));
			model->storeData(indices, 3 * 12 * sizeof(GLuint));
		}

		inline RawModel* getModel() { return model; }

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

		inline ~Cube() {
			delete model;
		}
	};

} }