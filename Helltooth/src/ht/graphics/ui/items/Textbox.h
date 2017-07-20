
#pragma once

#include "../GUIItem.h"

#include "graphics/rendering/2D/Sprite.h"

namespace ht { namespace graphics { namespace ui {

	class Textbox : public GUIItem {
	private:
		utils::String text, font;

		uint32 foreColor;
		maths::vec2 textPosition, scale;

		f32 pointer;

		uint16 maxCharCount;

		Sprite *background = nullptr;

	public:
		Textbox(f32 x, f32 y, f32 width, f32 height, utils::String font, uint16 fontSize,
			maths::vec2 space = maths::vec2(0.f,0.f), uint16 maxCharCount = 0);
		~Textbox();

		void submit(BatchRenderer2D* renderer) override;
		void update(const utils::Event& e) override;

		void updateText(const utils::Event& e);

		void setBackgroundColor(maths::vec4 color);
		void setBackgroundColor(uint32 color);

		void setTextColor(maths::vec4 color) {
			byte r = (byte)(color.x * 255.0f);
			byte g = (byte)(color.y * 255.0f);
			byte b = (byte)(color.z * 255.0f);
			byte a = (byte)(color.w * 255.0f);

			foreColor = a << 24 | b << 16 | g << 8 | r;
		}

		__forceinline void setTextColor(uint32 color) {
			foreColor = color;
		}
	};
} } }
