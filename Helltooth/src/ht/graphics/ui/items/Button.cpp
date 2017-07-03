#include "Button.h"

namespace ht { namespace graphics { namespace ui {
	using namespace maths;
	using namespace utils;

	Button::Button(String text, f32 x, f32 y, f32 width, f32 height, utils::String font, maths::vec2 space)
		: GUIItem(x, y, width, height), text(text), space(space), font(font) {

		FontManager::Get()->selectFont(font);
		vec3 size = getSize();

		scale.x = size.x / (width - space.x * 2.f);
		scale.y = (size.y - size.z) / (height - space.y * 2.f);

		textPosition.x = space.x;
		textPosition.y = space.y - (size.z / scale.y);
	}

	void Button::update(const Event &e) {
		if (e.handled)
			return;

		f32 mx = e.mouseX;
		f32 my = e.mouseY;

		updateButton(e, mx, my);
		if (mx >= size.x && mx <= (size.x + size.z) && my >= size.y && my <= (size.y + size.w)) {
			f_OnHover(e);
			for (unsigned int i = 0; i < MAX_BUTTONS; i++)
				if (e.mouse_buttons[i]) {
					f_OnClick(e);
					f_OnDrag(e);
				}
			e.handled = true;
		}
	}

	void Button::setText(utils::String &text) {
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

	void Button::submit(BatchRenderer2D* renderer) {
		if (!visible) return;

		FontManager::Get()->selectFont(font);

		renderer->push(transformation, true);
		renderer->submitText(text, textPosition.x, textPosition.y, foreColor, scale);
		for (Sprite* sprite : sprites)
			if (sprite)
				renderer->submit(sprite);
		renderer->pop();
	}

	vec3 Button::getSize() {
		Font f = FontManager::Get()->getFont();

		vec3 size;

		ftgl::texture_font_t* ftFont = f.font;

		for (unsigned int i = 0; i < text.size - 1; i++) {
			char c = text[i];
			ftgl::texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);

			if (glyph) {
				if (i > 0) {
					float kerning = ftgl::texture_glyph_get_kerning(glyph, text[i - 1]);
					size.x += kerning;
				}

				size.y = glyph->offset_y > size.y ? glyph->offset_y : size.y;
				int min = glyph->offset_y - glyph->height;
				size.z = min < size.z ? min : size.z;
				size.x += glyph->advance_x;
			}
		}
		return size;
	}

	void Button::updateButton(const Event& e, f32 mx, f32 my) {
		bool p = mx >= size.x && mx <= (size.x + size.z) && my >= size.y && my <= (size.y + size.w) && e.mouse_buttons[0];
		if (pressed != p) {
			pressed = p;
			if (!sprites.empty())
				sprites.clear();

			if (pressed) {
				if (pressedcolor)
					sprites.push_back(pressedcolor);
			}
			else
				if (background)
					sprites.push_back(background);
		}
	}

} } }