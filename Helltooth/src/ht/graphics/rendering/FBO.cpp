#include "FBO.h"

namespace ht { namespace graphics {

	FBO::FBO(GLuint width, GLuint height)
		: width(width), height(height) {
		glGenFramebuffers(1, &id);
		glBindFramebuffer(GL_FRAMEBUFFER, id);
		glDrawBuffer(GL_COLOR_ATTACHMENT0);
	}

	FBO::~FBO() {
		if (hasDepthBuffer)
			glDeleteFramebuffers(1, &depthBuffer);
		glDeleteFramebuffers(1, &id);
	}

	void FBO::createColorTexture() {
		Texture* texture = htnew Texture();
		texture->createAttachment(width, height, TEXTURE_COLOR_ATTACHMENT);
		glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, texture->getID(), 0);
		textures.push_back(TextureManager::Get()->addTexture(texture));
	}

	void FBO::createDepthTexture(bool texture) {
		hasDepthBuffer = !texture;
		if (texture) {
			Texture* texture = htnew Texture();
			texture->createAttachment(width, height, TEXTURE_DEPTH_ATTACHMENT);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, texture->getID(), 0);
			textures.push_back(TextureManager::Get()->addTexture(texture));
		}
		else {
			glGenRenderbuffers(1, &depthBuffer);
			glBindRenderbuffer(GL_RENDERBUFFER, depthBuffer);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthBuffer);
		}
	}


	void FBO::bind() {
		glBindTexture(GL_TEXTURE_2D, 0);
		glBindFramebuffer(GL_FRAMEBUFFER, id);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void FBO::unbind(int width, int height) {
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width, height);
	}

} }