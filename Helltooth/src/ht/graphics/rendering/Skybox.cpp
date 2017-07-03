#include "Skybox.h"

namespace ht { namespace graphics {
	using namespace utils;
	using namespace maths;

	String Skybox::skyboxVertex =
		#include "graphics/shaders/default/skybox.vert"
		;
	String Skybox::skyboxFragment =
		#include "graphics/shaders/default/skybox.frag"
		;

	Skybox::Skybox()
		: StaticEntity(nullptr) {
		hasShader = true;

		uint32 id = ShaderManager::Get()->loadProgram(skyboxVertex, skyboxFragment, false);
		program = ShaderManager::Get()->getProgram(id);

		//Cube created
		Cube* cube = htnew Cube();
		renderable = htnew Renderable();
		renderable->loadRawModel(cube->getModel());
		del cube;
		
		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	Skybox::~Skybox() {
		glDeleteTextures(1, &textureID);
	}

	void Skybox::setViewMatrix(mat4 camera) const {
		camera[0 + 3 * 4] = 0;
		camera[1 + 3 * 4] = 0;
		camera[2 + 3 * 4] = 0;
		program->uniformMat4("viewMatrix", camera);
	}

	void Skybox::setProjection(mat4 projection) const {
		if (program->hasProjection())
			return;

		program->start();
		program->setProjection("projectionMatrix", projection);
	}

	void Skybox::prepare() const {
		glDisable(GL_CULL_FACE);
		program->start();
	}

	void Skybox::render() const {
		program->start();
		glBindVertexArray(renderable->getVaoID());

		program->uniform1i("skybox", 0);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);


		renderable->render();
		renderable->end();
		program->stop();
		glEnable(GL_CULL_FACE);
	}

	void Skybox::addCubemap(assets::Cubemap* cubemap) {
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		switch (cubemap->bpp) {
		case 24:
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGB, cubemap->width, cubemap->height, 0, GL_BGR, GL_UNSIGNED_BYTE, cubemap->right);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGB, cubemap->width, cubemap->height, 0, GL_BGR, GL_UNSIGNED_BYTE, cubemap->left);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGB, cubemap->width, cubemap->height, 0, GL_BGR, GL_UNSIGNED_BYTE, cubemap->top);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGB, cubemap->width, cubemap->height, 0, GL_BGR, GL_UNSIGNED_BYTE, cubemap->bottom);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGB, cubemap->width, cubemap->height, 0, GL_BGR, GL_UNSIGNED_BYTE, cubemap->front);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGB, cubemap->width, cubemap->height, 0, GL_BGR, GL_UNSIGNED_BYTE, cubemap->back);
			break;
		case 32:
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, cubemap->width, cubemap->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, cubemap->right);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, cubemap->width, cubemap->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, cubemap->left);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, cubemap->width, cubemap->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, cubemap->top);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, cubemap->width, cubemap->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, cubemap->bottom);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, cubemap->width, cubemap->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, cubemap->front);
			glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, cubemap->width, cubemap->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, cubemap->back);
			break;
		}

		del cubemap;
	}
} }