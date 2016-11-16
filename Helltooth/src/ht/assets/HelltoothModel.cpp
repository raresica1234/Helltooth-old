#include "HelltoothModel.h"

namespace ht { namespace assets {

	HelltoothModel::HelltoothModel(String path) {
		Cereal::Buffer buffer(1);
		buffer.readFile(path.c_str());

		if (model) del model;

		Cereal::Database* db = htnew Cereal::Database();
		db->read(buffer);

		Cereal::Object* object = db->getObject("model");
		Cereal::Array* array = object->getArray("positions");
		GLfloat* positions = htnew GLfloat[array->getCount()];
		array->getRawArray<GLfloat>(positions);
		this->model = htnew RawModel(positions, array->getCount() * sizeof(GLfloat));

		Cereal::Array* indices = object->getArray("indices");
		if (indices) {
			GLuint* indicesArray = htnew GLuint[indices->getCount()];
			indices->getRawArray<GLint>((GLint*)indicesArray);
			model->storeData(indicesArray, indices->getCount() * sizeof(GLuint));
		}

		Cereal::Array* textureCoords = object->getArray("textureCoords");
		if (textureCoords) {
			GLfloat* textureCoordsArray = htnew GLfloat[textureCoords->getCount()];
			textureCoords->getRawArray<GLfloat>(textureCoordsArray);
			model->storeData(RAWMODEL_TEXTURE_COORDS, textureCoordsArray, textureCoords->getCount() * sizeof(GLfloat));
		}

		Cereal::Array* normals = object->getArray("normals");
		if (normals) {
			GLfloat* normalsArray = htnew GLfloat[normals->getCount()];
			normals->getRawArray<GLfloat>(normalsArray);
			model->storeData(RAWMODEL_NORMALS, normalsArray, normals->getCount() * sizeof(GLfloat));
		}
		del db;
	}

	void HelltoothModel::storeAsHelltoothModel(String path, RawModel* model) {
		Cereal::Object* object = htnew Cereal::Object("model");

		Cereal::Array* array = nullptr;
		Cereal::Array* indexArray = nullptr;
		Cereal::Array* textureCoordArray = nullptr;
		Cereal::Array* normalsArray = nullptr;

		GLfloat* positions = htnew GLfloat[model->getPositionSize() / sizeof(GLfloat)];
		memcpy(positions, model->getPositions(), model->getPositionSize());
		array = htnew Cereal::Array("positions", positions, model->getPositionSize() / sizeof(GLfloat));
		del[] positions;

		if (model->getIndexSize() > 0) {
			GLint* indices = htnew GLint[model->getIndexSize() / sizeof(GLuint)];
			memcpy(indices, model->getIndices(), model->getIndexSize());
			indexArray = htnew Cereal::Array("indices", indices, model->getIndexSize() / sizeof(GLint));
			del[] indices;
		}

		if (model->getTextureCoordsSize() > 0) {
			GLfloat* textureCoords = htnew GLfloat[model->getTextureCoordsSize() / sizeof(GLfloat)];
			memcpy(textureCoords, model->getTextureCoords(), model->getTextureCoordsSize());
			textureCoordArray = htnew Cereal::Array("textureCoords", textureCoords, model->getTextureCoordsSize() / sizeof(GLfloat));
			del[] textureCoords;
		}

		if (model->getNormalSize() > 0) {
			GLfloat* normals = htnew GLfloat[model->getNormalSize() / sizeof(GLfloat)];
			memcpy(normals, model->getNormals(), model->getNormalSize());
			normalsArray = htnew Cereal::Array("normals", normals, model->getNormalSize() / sizeof(GLfloat));
			del[] normals;
		}

		if (array)
			object->addArray(array);

		if (indexArray)
			object->addArray(indexArray);

		if (textureCoordArray)
			object->addArray(textureCoordArray);

		if (normalsArray)
			object->addArray(normalsArray);

		Cereal::Database* database = htnew Cereal::Database("model");
		database->addObject(object);

		Cereal::Buffer buffer = Cereal::Buffer(database->getSize());
		database->write(buffer);
		buffer.writeFile(path.c_str());
		del database;
	}

} }