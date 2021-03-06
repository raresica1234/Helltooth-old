#include "Renderable.h"

namespace ht { namespace graphics {

	Renderable::Renderable()
		: vboNumber(0), usingIbo(false), ibo(nullptr){
		this->vao = htnew VAO();
		this->vbos = htnew VBO[4];
	}

	Renderable::~Renderable() {
		del[] vbos;
		del vao;

		if (ibo != nullptr)
			del ibo;
	}

	void Renderable::loadRawModel(const RawModel* model) {
		//Store data for every single vbo from the models data.
		storeData(RENDERABLE_COORDS, model->getPositions(), model->getPositionSize());

		if (model->getIndexSize() > 0)
			//std::cout << model->getIndexSize();
			storeData(model->getIndices(), model->getIndexSize());

		if (model->getNormalSize() > 0)
			storeData(RENDERABLE_NORMALS ,model->getNormals(), model->getNormalSize());

		if (!model->usingColors())
			storeData(RENDERABLE_TEXTURE_COORDS, model->getTextureCoords(), model->getTextureCoordsSize());

		del model;
	}

	void Renderable::storeData(const int32 usage, const f32 *data, const uint32 &dataSize) {
		//Make new vbo and bind vao
			vao->bindVAO();

			vbos[vboNumber] = *(htnew VBO());
			vbos[vboNumber].bindVBO();
			switch (usage) {
			case RENDERABLE_COORDS:
				if (API::is2D())
					vbos[vboNumber].storeDataInAttribList(0, 2, dataSize, data);
				else
					vbos[vboNumber].storeDataInAttribList(0, 3, dataSize, data);
				break;
			case RENDERABLE_TEXTURE_COORDS:
				vbos[vboNumber].storeDataInAttribList(1, 2, dataSize, data);
				break;
			case RENDERABLE_NORMALS:
				vbos[vboNumber].storeDataInAttribList(2, 3, dataSize, data);
				break;
			}
			

			//Increase vbo numbers (number of vbos created)
			vboNumber++;
			vao->unbindVAO();
	}

	void Renderable::storeData(const uint32 *data, const uint32 &dataSize) {
		vao->bindVAO();

		ibo = htnew IBO();
		ibo->bindIBO();

		ibo->storeIndices(data, dataSize);
		usingIbo = true;


		vao->unbindVAO();
	}

	void Renderable::prepare() const {
		vao->bindVAO();
		for (size_t i = 0; i < textures.size(); i++) {
			if (i > 31) {
				HT_WARN("[Renderable] Textures size is bigger than 32!");
				break;
			}
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, textures[i]->getID());
		}
	}

	void Renderable::render() const {
		if (usingIbo) {
			glDrawElements(GL_TRIANGLES, ibo->getCount(), GL_UNSIGNED_INT, nullptr);
		}
		else
			glDrawArrays(GL_TRIANGLES, 0, 3);
	}

} }