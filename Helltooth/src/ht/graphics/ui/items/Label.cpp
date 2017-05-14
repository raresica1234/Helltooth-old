#include "Label.h"

namespace ht { namespace graphics { namespace ui {
	using namespace maths;
	using namespace utils;

	Label::Label(String text, f32 x, f32 y, f32 width, f32 height, String font, vec2 space)
		: GUIItem(x, y, width, height), text(text), space(space), font(font) {

		FontManager::Get()->selectFont(font);
		vec3 size = getSize();

		scale.x = size.x / (width - space.x * 2.f);
		scale.y = (size.y - size.z) / (height - space.y * 2.f);

		textPosition.x = space.x;
		textPosition.y = space.y - (size.z / scale.y);
	}

	void Label::submit(BatchRenderer2D* renderer) {
		if (!visible) return;

		FontManager::Get()->selectFont(font);

		renderer->push(transformation, true);
		renderer->submitText(text, textPosition.x, textPosition.y, foreColor, scale);
		for (Sprite* sprite : sprites)
			if(sprite)
				renderer->submit(sprite);
		renderer->pop();
	}

	vec3 Label::getSize() {
		Font f = FontManager::Get()->getFont();

		vec3 size;

		ftgl::texture_font_t* ftFont = f.font;

		for (uint32 i = 0; i < text.size - 1; i++) {
			char c = text[i];
			ftgl::texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);

			if (glyph) {
				if (i > 0) {
					f32 kerning = ftgl::texture_glyph_get_kerning(glyph, text[i - 1]);
					size.x += kerning;
				}

				size.y = glyph->offset_y > size.y ? glyph->offset_y : size.y;
				int32 min = glyph->offset_y - glyph->height;
				size.z = min < size.z ? min : size.z;
				//if (i == 0)
				//	size.x += glyph->width;
				//else
					size.x += glyph->advance_x;
			}
		}
		return size;
	}

} } }

