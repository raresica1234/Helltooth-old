#pragma once

#include "../Layer.h"

#include "../rendering/renderers/2D/BatchRenderer2D.h"

#include "../../utils/String.h"

namespace ht { namespace graphics {

	class GUILayer : public Layer {
	private:
		static utils::String uiShaderVert;
		static utils::String uiShaderFrag;

	protected:
		BatchRenderer2D* renderer;
		ShaderProgram* shader;

		unsigned int width, height;

	public:
		GUILayer(const unsigned int &width, const unsigned int &height);
		~GUILayer();

		void setMatrix(maths::mat4 &projectionMatrix) override;

		__forceinline void begin() {
			glEnable(GL_BLEND);
			renderer->begin();
			shader->start();
		}

		void submit(Sprite* sprite) {
			renderer->submit(sprite);
		}

		void submit(utils::String text, float x, float y, maths::vec4 col) {
			renderer->submitText(text, x, height - y, col);
		}

		void load(bool &loaded) override { loaded = true; }

		void render() override {
			renderer->end();
			renderer->render();
			shader->stop();
			glDisable(GL_BLEND);
		}

		void tick() override {}

		void update(const utils::Event& e) override;

		void reloadTextures() override {
			shader->start();
			GLint texIDs[] = {
				0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31
			};
			shader->uniform1iv("textures", texIDs, 32);
			shader->setProjection("projectionMatrix", projectionMatrix);
		}
	};

} }
