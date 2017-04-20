#include "GBuffer.h"

namespace ht { namespace graphics {

	GBuffer::GBuffer() {
		glGenFramebuffers(1, &fbo);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);

		Window* w = WindowManager::Get()->getWindow(0);
		width = w->getWidth();
		height = w->getHeight();

		for (GLuint i = 0; i < 3; i++) {
			Texture* current = htnew Texture();
			TextureManager::Get()->addTexture(current);
			current->createAttachment(width, height, TEXTURE_COLOR_ATTACHMENT);
			glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, current->getID(), 0);
			textures.push_back(current);
		}
		Texture* depth = htnew Texture();
		TextureManager::Get()->addTexture(depth);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth->getID(), 0);

		//when adding or removing frame buffer's render targets change this idiot
		GLenum DrawBuffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
		glDrawBuffers(3, DrawBuffers);

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	GBuffer::~GBuffer() {
		glDeleteFramebuffers(1, &fbo);
	}

	void GBuffer::bind() {
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void GBuffer::unbind(const int &width, const int &height) {
		if (this->width != width || this->height != height);
		//TODO: Resizing!

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

} }