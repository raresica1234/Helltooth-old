#include "GUILayer.h"

namespace ht { namespace graphics {
	using namespace utils;

	String GUILayer::uiShaderVert = 
							#include "UiShader.vert"
							;
	String GUILayer::uiShaderFrag = 
							#include "UiShader.frag"
							;

	GUILayer::GUILayer()
		: Layer(nullptr) {
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
		shader->uniform1iv("textures", texIDs, 32);
	}

	GUILayer::~GUILayer() {
		del renderer;
	}

	void GUILayer::setMatrix(maths::mat4 &projectionMatrix) {
		shader->start();
		shader->setProjection("projectionMatrix", projectionMatrix);
	}

	void GUILayer::update() {}

} }
