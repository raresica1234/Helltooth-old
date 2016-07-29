#pragma once

#include <GLFW/glfw3.h>
#include "../Renderable.h"
#include "RawModel.h"
#include "../../../utils/memory/MemoryManager.h"

namespace ht { namespace graphics {

	struct Quad {
		GLfloat *data;

		//Indices of the cube model
		GLuint *indices;

		GLfloat *textureCoords;

		RawModel *model;

		inline Quad() {
			init();
			model = htnew RawModel(data, 3 * 4 * sizeof(GLfloat));
			model->storeData(indices, 3 * 12 * sizeof(GLuint));
			model->storeData(RAWMODEL_TEXTURE_COORDS, textureCoords, 2 * 4 * 6 * sizeof(GLfloat));
		}

		inline ~Quad() {}
		
		inline RawModel* getModel() { return model; }

	protected:
		void init() {
			data = htnew GLfloat[4 * 3]{
				-1.0f, -1.0f, 0.0f,
				 1.0f, -1.0f, 0.0f,
				 1.0f,  1.0f, 0.0f,
				-1.0f,  1.0f, 0.0f
			};

			textureCoords = htnew GLfloat[4 * 2]{
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 1.0f
			};

			indices = htnew GLuint[6]{
				0,1,2,
				0,2,3
			};
		}

	};

} }