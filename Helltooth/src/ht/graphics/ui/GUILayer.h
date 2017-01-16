#pragma once
#include "../rendering/renderers/2D/BatchRenderer2D.h"
#include "../Layer.h"

#include "../../utils/String.h"

namespace ht { namespace graphics {

	class GUILayer : public Layer {
	private:
		BatchRenderer2D* renderer;

		bool begin = false;

		static utils::String uiShaderVert;
		static utils::String uiShaderFrag;

		ShaderProgram* shader;

	public:
		GUILayer();
		~GUILayer();

		void setMatrix(maths::mat4 &projectionMatrix) override;

		void submit(Sprite* sprite) {
			shader->start();
			if (!begin) {
				renderer->begin();
				begin = true;
			}
			renderer->submit(sprite);
		}

		void load(bool &loaded) override { loaded = true; }

		void render() override {
			begin = false;
			renderer->end();
			renderer->render();
			shader->stop();
		}

		void update() override;
	};

} }
