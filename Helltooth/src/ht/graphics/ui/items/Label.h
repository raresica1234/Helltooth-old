#pragma once

#include "../GUIItem.h"

#include "utils/String.h"
#include "utils/input/Input.h"

#include "graphics/ui/font/FontManager.h"

namespace ht { namespace graphics { namespace ui {

	class Label : public GUIItem {
	private:
		utils::String text;
		maths::vec2 textPosition;

		maths::vec2 scale = maths::vec2(1.f, 1.f);

		maths::vec2 space;

		utils::String font;

		enum TextAttrib {
			FILL = 0
		} attrib = FILL;

		enum Align {
			CENTER,
			LEFT,
			RIGHT
		} align = CENTER;

		unsigned int foreColor = 0x000000FF;

		Sprite* background = nullptr;

	public:

		Label(utils::String text, float x, float y, float width, float height, utils::String font, maths::vec2 space = maths::vec2(0.f, 0.f));
		~Label() { if (background) del background; }

		__forceinline void setBackgroundColor(unsigned int color) {
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
			int r = (int)(color.x * 255.0f);
			int g = (int)(color.y * 255.0f);
			int b = (int)(color.z * 255.0f);
			int a = (int)(color.w * 255.0f);

			unsigned int col = a << 24 | b << 16 | g << 8 | r;
			setBackgroundColor(col);
		}

		void submit(BatchRenderer2D* renderer) override;

	protected:
		maths::vec3 getSize();
	};

} } }
