#include "HelltoothModel.h"

namespace ht { namespace assets {
	using namespace utils;
	using namespace graphics;

	HelltoothModel::HelltoothModel(String path) {
		Cereal::Buffer buffer(1);
		buffer.readFile(path.c_str());

		if (model) del model;

		Cereal::Database* db = htnew Cereal::Database();
		db->read(buffer);

		Cereal::Object* object = db->getObject("model");
		Cereal::Array* array = object->getArray("positions");

		f32* positions = htnew f32[array->getCount()];
		array->getRawArray<f32>(positions);
		this->model = htnew RawModel(positions, array->getCount() * sizeof(f32));

		Cereal::Array* indices = object->getArray("indices");
		if (indices) {
			uint32* indicesArray = htnew uint32[indices->getCount()];
			indices->getRawArray<int32>((int32*)indicesArray);
			model->storeData(indicesArray, indices->getCount() * sizeof(uint32));
		}

		Cereal::Array* textureCoords = object->getArray("textureCoords");
		if (textureCoords) {
			f32* textureCoordsArray = htnew f32[textureCoords->getCount()];
			textureCoords->getRawArray<f32>(textureCoordsArray);
			model->storeData(RAWMODEL_TEXTURE_COORDS, textureCoordsArray, textureCoords->getCount() * sizeof(f32));
		}

		Cereal::Array* normals = object->getArray("normals");
		if (normals) {
			f32* normalsArray = htnew f32[normals->getCount()];
			normals->getRawArray<f32>(normalsArray);
			model->storeData(RAWMODEL_NORMALS, normalsArray, normals->getCount() * sizeof(f32));
		}
		del db;
	}

	void HelltoothModel::StoreAsHelltoothModel(String path, RawModel* model) {
		Cereal::Object* object = htnew Cereal::Object("model");

		Cereal::Array* array = nullptr;
		Cereal::Array* indexArray = nullptr;
		Cereal::Array* textureCoordArray = nullptr;
		Cereal::Array* normalsArray = nullptr;

		f32* positions = htnew f32[model->getPositionSize() / sizeof(f32)];
		memcpy(positions, model->getPositions(), model->getPositionSize());
		array = htnew Cereal::Array("positions", positions, model->getPositionSize() / sizeof(f32));
		del[] positions;

		if (model->getIndexSize() > 0) {
			int32* indices = htnew int32[model->getIndexSize() / sizeof(GLuint)];
			memcpy(indices, model->getIndices(), model->getIndexSize());
			indexArray = htnew Cereal::Array("indices", indices, model->getIndexSize() / sizeof(int32));
			del[] indices;
		}

		if (model->getTextureCoordsSize() > 0) {
			f32* textureCoords = htnew f32[model->getTextureCoordsSize() / sizeof(f32)];
			memcpy(textureCoords, model->getTextureCoords(), model->getTextureCoordsSize());
			textureCoordArray = htnew Cereal::Array("textureCoords", textureCoords, model->getTextureCoordsSize() / sizeof(f32));
			del[] textureCoords;
		}

		if (model->getNormalSize() > 0) {
			f32* normals = htnew f32[model->getNormalSize() / sizeof(f32)];
			memcpy(normals, model->getNormals(), model->getNormalSize());
			normalsArray = htnew Cereal::Array("normals", normals, model->getNormalSize() / sizeof(f32));
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