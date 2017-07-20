#include "Textbox.h"

namespace ht { namespace graphics { namespace ui {
	using namespace utils;
	using namespace maths;

	Textbox::Textbox(f32 x, f32 y, f32 width, f32 height, String font, uint16 fontSize, vec2 space, uint16 maxCharCount)
		: GUIItem(x, y, width, height), font(font), maxCharCount(maxCharCount)	{
		FontManager::Get()->selectFont(font);
		Font& fontt = FontManager::Get()->getFont();

		scale.x = fontSize / font.size;
		scale.y = fontSize / font.size;

		textPosition = space;
		
		if (maxCharCount == 0) {
			ftgl::texture_glyph_t* glyph = ftgl::texture_font_get_glyph(fontt.font, 'W');
			f32 xSize = glyph->advance_x / scale.x;
			this->maxCharCount = width / xSize;
		}
	}

	Textbox::~Textbox() {
		del background;
	}

	void Textbox::submit(BatchRenderer2D* renderer) {
		if (!visible) return;

		FontManager::Get()->selectFont(font);

		renderer->push(transformation, true);
		renderer->submitText(text, textPosition.x, textPosition.y, foreColor, scale);
		for (Sprite* sprite : sprites)
			if (sprite)
				renderer->submit(sprite);
		renderer->pop();
	}

	void Textbox::update(const Event& e) {
		if (e.handled)
			return;

		float my = e.mouseY;
		float mx = e.mouseX;

		if (mx >= size.x && mx <= (size.x + size.z) && my >= size.y && my <= (size.y + size.w)) {
			f_OnHover(e, this);
			updateText(e);
			for (unsigned int i = 0; i < MAX_BUTTONS; i++)
				if (e.mouse_buttons[i]) {
					f_OnClick(e, this);
					f_OnDrag(e, this);
				}
			e.handled = true;
		}
	}

	void Textbox::updateText(const Event& e) {
		if (text.size - 1 < maxCharCount) {
			if (e.isHold(GLFW_KEY_LEFT_SHIFT) || e.isHold(GLFW_KEY_RIGHT_SHIFT)) {
				for (int i = GLFW_KEY_A; i <= GLFW_KEY_Z; i++)
					if (e.isPressed(i)) text += e.toChar(i);
				if (e.isPressed(GLFW_KEY_APOSTROPHE)) text += '"';
				if (e.isPressed(GLFW_KEY_COMMA)) text += '<';
				if (e.isPressed(GLFW_KEY_MINUS)) text += '_';
				if (e.isPressed(GLFW_KEY_PERIOD)) text += '>';
				if (e.isPressed(GLFW_KEY_SLASH)) text += '?';
				if (e.isPressed(GLFW_KEY_0)) text += ')';
				if (e.isPressed(GLFW_KEY_1)) text += '!';
				if (e.isPressed(GLFW_KEY_2)) text += '@';
				if (e.isPressed(GLFW_KEY_3)) text += '#';
				if (e.isPressed(GLFW_KEY_4)) text += '$';
				if (e.isPressed(GLFW_KEY_5)) text += '%';
				if (e.isPressed(GLFW_KEY_6)) text += '^';
				if (e.isPressed(GLFW_KEY_7)) text += '&';
				if (e.isPressed(GLFW_KEY_8)) text += '*';
				if (e.isPressed(GLFW_KEY_9)) text += '(';
				if (e.isPressed(GLFW_KEY_SEMICOLON)) text += ':';
				if (e.isPressed(GLFW_KEY_EQUAL)) text += '+';
				if (e.isPressed(GLFW_KEY_LEFT_BRACKET)) text += '{';
				if (e.isPressed(GLFW_KEY_BACKSLASH)) text += '|';
				if (e.isPressed(GLFW_KEY_RIGHT_BRACKET)) text += '}';
				if (e.isPressed(GLFW_KEY_GRAVE_ACCENT)) text += '~';
			}
			else {
				for (int i = GLFW_KEY_A; i <= GLFW_KEY_Z; i++)
					if (e.isPressed(i)) text += (e.toChar(i) + 32);
				for (int i = GLFW_KEY_APOSTROPHE; i <= GLFW_KEY_EQUAL; i++)
					if (e.isPressed(i)) text += e.toChar(i);
				for (int i = GLFW_KEY_LEFT_BRACKET; i <= GLFW_KEY_GRAVE_ACCENT; i++)
					if (e.isPressed(i)) text += e.toChar(i);
			}

			if (e.isPressed(GLFW_KEY_SPACE)) text += ' ';
		}
		if (e.isPressed(GLFW_KEY_BACKSPACE)) text--;
	}

	void Textbox::setBackgroundColor(vec4 color) {
		if (!background) {
			background = htnew Sprite(0, 0, size.z, size.w);
			sprites.push_back(background);
		}
		background->setColor(color);
	}

	void Textbox::setBackgroundColor(uint32 color) {
		if (!background) {
			background = htnew Sprite(0, 0, size.z, size.w);
			sprites.push_back(background);
		}
		background->setColor(color);
	}
} } }