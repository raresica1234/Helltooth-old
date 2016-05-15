#pragma once

#include <GLFW/glfw3.h>
#include "../Renderable.h"

#include "../../../utils/memory/MemoryManager.h" // include this file in all the files that use "new" or "delete"

namespace ht { namespace graphics {

	struct Cube {
		GLfloat* data;
		GLint* indices;

		Cube(Renderable *renderable) {
			init();
			renderable->bindVAO();
			renderable->addBufferData(data, 3 * 4 * 6 * sizeof(GLfloat), RENDERABLE_COORDS);
			renderable->addBufferData(indices, 3 * 12 * sizeof(GLint));
			renderable->unbindVAO();
		}

		void init()
		{
			this->data = new GLfloat[3 * 4 * 6]
			{
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

			this->indices = new GLint[3 * 12]
			{
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

		~Cube()
		{
			//delete[] this->data; -> is this already deleted? I get an exception...
			//delete[] this->indices;
		}
	};

} }