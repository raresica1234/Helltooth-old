#pragma once

#include "GUIItem.h"

#include "../Layer.h"
#include "../rendering/renderers/2D/BatchRenderer2D.h"

#include "items/Label.h"
#include "items/Button.h"
#include "items/Image.h"
#include "items/Slider.h"
#include "items/Textbox.h"

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
		GUILayer(const uint32 width, const uint32 height);
		~GUILayer();

		void setMatrix(maths::mat4 &projectionMatrix) override;

		__forceinline void begin() {
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			renderer->begin();
			shader->start();
		}


		__forceinline ui::Label* createLabel(utils::String text, f32 x, f32 y, f32 width,
			f32 height, utils::String font, maths::vec2 space = maths::vec2(0.0f, 0.0f)) {
			ui::Label* label = htnew ui::Label(text, x, this->height - y - height, width, height, font, space);
			items.push_back(label);
			return label;
		}

		__forceinline ui::Button* createButton(utils::String text, f32 x, f32 y, f32 width,
			f32 height, utils::String font, maths::vec2 space = maths::vec2(0.0f, 0.0f)) {
			ui::Button* button = htnew ui::Button(text, x, this->height - y - height, width, height, font, space);
			items.push_back(button);
			return button;
		}

		__forceinline ui::Image* createImage(const Texture* texture, f32 x, f32 y, f32 width, f32 height) {
			ui::Image* image = htnew ui::Image(texture, x, this->height - y - height, width, height);
			items.push_back(image);
			return image;
		}
		
		__forceinline ui::Image* createImage(uint32 textureID, f32 x, f32 y, f32 width, f32 height) {
			ui::Image* image = htnew ui::Image(textureID, x, this->height - y - height, width, height);
			items.push_back(image);
			return image;
		}

		__forceinline ui::Slider* createSlider(f32 x, f32 y, f32 width, f32 height, uint32 steps, bool horizontal = true) {
			ui::Slider* slider = htnew ui::Slider(x, this->height - y - height, width, height, steps, horizontal);
			items.push_back(slider);
			return slider;
		}

		__forceinline ui::Textbox* createTextbox(f32 x, f32 y, f32 width, f32 height, utils::String font, uint16 fontSize,
			maths::vec2 space = maths::vec2(0.f, 0.f), uint16 maxCharCount = 0) {
			ui::Textbox* textbox = htnew ui::Textbox(x, this->height - y - height, width, height, font, fontSize, space, maxCharCount);
			items.push_back(textbox);
			return textbox;
		}

		__forceinline void submit(Sprite* sprite) {
			renderer->submit(sprite);
		}

		__forceinline void submit(utils::String text, f32 x, f32 y, maths::vec4 col, maths::vec2 scale = maths::vec2(1.f, 1.f)) {
			renderer->submitText(text, x, height - y, col, scale);
		}

		__forceinline void submit(utils::String text, f32 x, f32 y, uint32 col, maths::vec2 scale = maths::vec2(1.f, 1.f)) {
			renderer->submitText(text, x, height - y, col, scale);
		}

		__forceinline void submitGUI() {
			for (ui::GUIItem* item : items) {
				item->submit(renderer);
			}
		}

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
			for (ui::GUIItem* item : items) {
				item->update(event);
				if (event.handled)
					e.handled = true;

				memcpy(e.previously_pressed, event.previously_pressed, MAX_KEYS);
				memcpy(e.keys, event.keys, MAX_KEYS);
			}
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
