#pragma once

#include "../GUIItem.h"

#include "graphics/ui/font/FontManager.h"

#include "utils/Internal.h"
#include "utils/String.h"
#include "utils/input/Input.h"

namespace ht { namespace graphics { namespace ui {

	class Button : public GUIItem {
	private:
		utils::String text, font;
		maths::vec2 textPosition, scale = maths::vec2(1.f, 1.f), space;

		uint32 foreColor = 0x000000FF;

		Sprite *background = nullptr, *pressedcolor = nullptr;

		bool pressed = false;

	public:
		Button(utils::String text, f32 x, f32 y, f32 width, f32 height, utils::String font, maths::vec2 space = maths::vec2(0.f, 0.f));
		~Button() { if (background) del background; }

		__forceinline void setBackgroundColor(uint32 color) {
			if (!background) { background = htnew Sprite(0, 0, size.z, size.w); sprites.push_back(background); }
			background->setColor(color);
		}

		__forceinline void setPressedColor(uint32 color) { if (!pressedcolor) { pressedcolor = htnew Sprite(0, 0, size.z, size.w); } pressedcolor->setColor(color); }

		void update(const utils::Event &e) override;
		void setText(utils::String &text);
		void submit(BatchRenderer2D* renderer) override;

	protected:
		maths::vec3 getSize();
		void updateButton(const utils::Event& e, f32 mx, f32 my);
	};
} } }
