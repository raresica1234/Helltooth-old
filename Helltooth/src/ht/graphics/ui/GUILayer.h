#pragma once

#include "GUIItem.h"

#include "../Layer.h"
#include "../rendering/renderers/2D/BatchRenderer2D.h"

#include "items/Label.h"
#include "items/Button.h"
#include "items/Image.h"

#include "../../utils/String.h"

namespace ht { namespace graphics {

	class GUILayer : public Layer {
	private:
		static utils::String uiShaderVert;
		static utils::String uiShaderFrag;

		std::vector<ui::GUIItem*> items;
		
		Window* w;
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

		__forceinline ui::Label* createLabel(utils::String text, float x, float y, float width,
			float height, utils::String font, maths::vec2 space = maths::vec2(0.0f, 0.0f)) {
			ui::Label* label = htnew ui::Label(text, x, this->height - y - height, width, height, font, space);
			items.push_back(label);
			return label;
		}

		__forceinline ui::Button* createButton(utils::String text, float x, float y, float width,
			float height, utils::String font, maths::vec2 space = maths::vec2(0.0f, 0.0f)) {
			ui::Button* button = htnew ui::Button(text, x, this->height - y - height, width, height, font, space);
			items.push_back(button);
			return button;
		}

		__forceinline ui::Image* createImage(const Texture* texture, float x, float y, float width, float height) {
			ui::Image* image = htnew ui::Image(texture, x, this->height - y - height, width, height);
			items.push_back(image);
			return image;
		}
		
		__forceinline ui::Image* createImage(unsigned int textureID, float x, float y, float width, float height) {
			ui::Image* image = htnew ui::Image(textureID, x, this->height - y - height, width, height);
			items.push_back(image);
			return image;
		}

		__forceinline void submit(Sprite* sprite) {
			renderer->submit(sprite);
		}

		__forceinline void submit(utils::String text, float x, float y, maths::vec4 col, maths::vec2 scale = maths::vec2(1.f, 1.f)) {
			renderer->submitText(text, x, height - y, col, scale);
		}

		__forceinline void submit(utils::String text, float x, float y, unsigned int col, maths::vec2 scale = maths::vec2(1.f, 1.f)) {
			renderer->submitText(text, x, height - y, col, scale);
		}

		__forceinline void submitGUI() {
			for (ui::GUIItem* item : items) {
				item->submit(renderer);
			}
		}

		__forceinline void load(bool &loaded) override { loaded = true; }

		__forceinline void render() override {
			renderer->end();
			renderer->render();
			shader->stop();
			glDisable(GL_BLEND);
		}

		__forceinline void tick() override {}

		__forceinline void update(const utils::Event& e) override {
			utils::Event event = e;
			event.mouseY = height - e.mouseY / w->getHeight() * height;
			event.mouseX = e.mouseX / w->getWidth() * width;
			for (ui::GUIItem* item : items)
				item->update(event);
		}

		 __forceinline void reloadTextures() override {
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
