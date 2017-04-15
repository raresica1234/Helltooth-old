#include "Skybox.h"

namespace ht { namespace graphics {
	using namespace utils;
	using namespace maths;

	utils::String Skybox::skyboxVertex =
		#include "graphics/shaders/default/skybox.vert"
		;
	utils::String Skybox::skyboxFragment =
		#include "graphics/shaders/default/skybox.frag"
		;

	Skybox::Skybox()
		: StaticEntity(nullptr) {
		hasShader = true;

		unsigned int id = ShaderManager::Get()->loadProgram(skyboxVertex, skyboxFragment, false);
		program = ShaderManager::Get()->getProgram(id);

		//Cube created
		Cube* cube = htnew Cube();
		renderable = htnew Renderable();
		renderable->loadRawModel(cube->getModel());
		del cube;

		glGenTextures(1, &textureID);
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
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
	}

	void Skybox::addTexture(assets::TextureData* textureData, Face face) {
		glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
		switch (textureData->bpp) {
		case 24:
			glTexImage2D((GLenum)face, 0, GL_RGB, textureData->width, textureData->height, 0, GL_BGR, GL_UNSIGNED_BYTE, textureData->pixels); break;

		case 32:
			glTexImage2D((GLenum)face, 0, GL_RGBA, textureData->width, textureData->height, 0, GL_BGRA, GL_UNSIGNED_BYTE, textureData->pixels); break;
		}
		del textureData;
	}

} }