#include "GUILayer.h"

namespace ht { namespace graphics {
	using namespace utils;

	String GUILayer::uiShaderVert = 
							#include "UiShader.vert"
							;
	String GUILayer::uiShaderFrag = 
							#include "UiShader.frag"
							;

	GUILayer::GUILayer(const unsigned int &width, const unsigned int &height)
		: Layer(nullptr), width(width), height(height) {
		renderer = htnew BatchRenderer2D();
		unsigned int id = API::createShader(GUILayer::uiShaderVert, GUILayer::uiShaderFrag, false);
		shader = ShaderManager::Get()->getProgram(id);
		shader->start();
		GLint texIDs[] = {
			0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
			10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
			20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
			30, 31
		};

		id = 0;
		w = WindowManager::Get()->getWindow(id);

		shader->uniform1iv("textures", texIDs, 32);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glDisable(GL_BLEND);
	}

	GUILayer::~GUILayer() {
		del renderer;
	}

	void GUILayer::setMatrix(maths::mat4 &projectionMatrix) {
		shader->start();
		shader->setProjection("projectionMatrix", projectionMatrix);
		this->projectionMatrix = projectionMatrix;
	}

} }
