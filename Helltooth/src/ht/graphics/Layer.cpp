#include "Layer.h"

namespace ht { namespace graphics { 

	Layer::Layer(Camera* camera, bool deferred)
		:camera(camera), deferred(deferred) {
		defaultRenderer();
	}

	Layer::~Layer() {
		del renderer;
		del camera;
	}

	void Layer::setMatrix(maths::mat4 &projectionMatrix) {
		this->projectionMatrix = projectionMatrix;
		renderer->setProjection(projectionMatrix);
	}
} }