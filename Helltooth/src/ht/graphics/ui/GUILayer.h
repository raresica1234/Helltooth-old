#pragma once
#include "../rendering/renderers/2D/BatchRenderer2D.h"
#include "../Layer.h"

#include "../../utils/String.h"

namespace ht { namespace graphics {

	class GUILayer : public Layer {
	private:
		static utils::String uiShaderVert;
		static utils::String uiShaderFrag;

	protected:
		BatchRenderer2D* renderer;
		ShaderProgram* shader;

	public:
		GUILayer();
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
			renderer->submitText(text, x, y, col);
		}

		void load(bool &loaded) override { loaded = true; }

		void render() override {
			renderer->end();
			renderer->render();
			shader->stop();
			glDisable(GL_BLEND);
		}

		void update() override;
	};

} }
