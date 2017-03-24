#pragma once

#include "../GUIItem.h"

#include "utils/String.h"
#include "utils/input/Input.h"

#include "graphics/ui/font/FontManager.h"

namespace ht { namespace graphics { namespace ui {

	class Button : public GUIItem {
	private:
		utils::String text;
		maths::vec2 textPosition;

		maths::vec2 scale = maths::vec2(1.f, 1.f);

		maths::vec2 space;

		utils::String font;

		unsigned int foreColor = 0x000000FF;

		Sprite *background = nullptr, *pressedcolor = nullptr;

		bool pressed = false;
	public:
		Button(utils::String text, float x, float y, float width, float height, utils::String font, maths::vec2 space = maths::vec2(0.f, 0.f));
		~Button() { if (background) del background; }

		__forceinline void setBackgroundColor(unsigned int color) {
			if (!background) {
				background = htnew Sprite(0, 0, size.z, size.w);
				sprites.push_back(background);
			}
			background->setColor(color);
		}

		__forceinline void setPressedColor(unsigned int color) {
			if (!pressedcolor) {
				pressedcolor = htnew Sprite(0, 0, size.z, size.w);
			}
			pressedcolor->setColor(color);
		}


		__forceinline void update(const utils::Event &e) override {
			float mx = e.mouseX;
			float my = e.mouseY;

			updateButton(e, mx, my);
			if (mx >= size.x && mx <= (size.x + size.z) && my >= size.y && my <= (size.y + size.w)) {
				f_OnHover(e);
				for (unsigned int i = 0; i < MAX_BUTTONS; i++)
					if (e.mouse_buttons[i]) {
						f_OnClick(e);
						f_OnDrag(e);
					}
			}
		}


		__forceinline void setText(utils::String &text) {
			FontManager::Get()->selectFont(font);

			this->text = utils::String(text);
			this->text.size = text.size;

			scale = maths::vec2();
			maths::vec3 textSize = getSize();

			scale.x = textSize.x / (size.z - (space.x * 2.f));
			scale.y = (textSize.y - textSize.z) / (size.w - (space.y * 2.f));

			textPosition.x = space.x;
			textPosition.y = space.y - (textSize.z / scale.y);
		}

		void submit(BatchRenderer2D* renderer) override;

	protected:
		maths::vec3 getSize();

		void updateButton(const utils::Event& e, float mx, float my) {
			bool p = mx >= size.x && mx <= (size.x + size.z) && my >= size.y && my <= (size.y + size.w) && e.mouse_buttons[0];
			if (pressed != p) {
				pressed = p;
				if (!sprites.empty())
					sprites.clear();

				if (pressed) {
					if (pressedcolor)
						sprites.push_back(pressedcolor);
				} else
					if(background)
						sprites.push_back(background);
			}
		}
	};



} } }
