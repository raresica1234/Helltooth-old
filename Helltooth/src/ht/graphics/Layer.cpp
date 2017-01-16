#include "Layer.h"

namespace ht { namespace graphics { 

	Layer::Layer(unsigned int shader, Camera* camera)
		: shader(ShaderManager::Get()->getProgram(shader)), camera(camera){
		this->shader->start();
		GLint texIDs[] = {
			0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
			30, 31
		};
		this->shader->uniform1iv("textures", texIDs, 32);
		defaultRenderer();
	}

	Layer::Layer(ShaderProgram* shader, Camera* camera)
		: shader(shader), camera(camera) {
		if (shader) {
			this->shader->start();
			GLint texIDs[] = {
				0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31
			};
			this->shader->uniform1iv("textures", texIDs, 32);
		}
		defaultRenderer();
	}

	Layer::~Layer() {
		del renderer;
		del camera;
	}

	void Layer::setMatrix(maths::mat4 &projectionMatrix) {
		this->projectionMatrix = projectionMatrix;
		shader->start();
		shader->setProjection("projectionMatrix", projectionMatrix);
		renderer->setProjection(projectionMatrix);
		shader->stop();
	}

	void Layer::cleanUP() {
		renderer->cleanUP();
	}

	void Layer::forceCleanUP() {
		renderer->forceCleanUP();
	}

	void Layer::reloadTextures() {
		if (shader) {
			this->shader->start();
			GLint texIDs[] = {
				0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31
			};
			this->shader->uniform1iv("textures", texIDs, 32);
		}
	}

	void Layer::defaultRenderer() {
		renderer = htnew SimpleRenderer(shader, camera);
	}
} }