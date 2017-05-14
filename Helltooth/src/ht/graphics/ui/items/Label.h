#pragma once

#include "../GUIItem.h"

#include "utils/String.h"
#include "utils/input/Input.h"

#include "graphics/ui/font/FontManager.h"

namespace ht { namespace graphics { namespace ui {

	class Label : public GUIItem {
	private:
		utils::String text, font;
		maths::vec2 textPosition, scale = maths::vec2(1.f, 1.f), space;

		enum TextAttrib { FILL = 0 } attrib = FILL;

		enum Align { CENTER, LEFT, RIGHT } align = CENTER;

		uint32 foreColor = 0x000000FF;

		Sprite* background = nullptr;

	public:
		Label(utils::String text, f32 x, f32 y, f32 width, f32 height, utils::String font, maths::vec2 space = maths::vec2(0.f, 0.f));
		~Label() { if (background) del background; }

		__forceinline void setBackgroundColor(uint32 color) {
			if (!background) {
				background = htnew Sprite(0, 0, size.z, size.w);
				sprites.push_back(background);
			}
			background->setColor(color);
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

		__forceinline void setBackgroundColor(maths::vec4 color) {
			byte r = (byte)(color.x * 255.0f);
			byte g = (byte)(color.y * 255.0f);
			byte b = (byte)(color.z * 255.0f);
			byte a = (byte)(color.w * 255.0f);

			uint32 col = a << 24 | b << 16 | g << 8 | r;
			setBackgroundColor(col);
		}

		void submit(BatchRenderer2D* renderer) override;

	protected:
		maths::vec3 getSize();
	};

} } }
