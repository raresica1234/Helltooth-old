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

		void submit(BatchRenderer2D* renderer) override;

		void setText(utils::String &text);
		
		void setBackgroundColor(uint32 color);
		void setBackgroundColor(maths::vec4 color);

	protected:
		maths::vec3 getSize();
	};

} } }
