#pragma once

#include "../GUIItem.h"

#include "utils/String.h"
#include "utils/input/Input.h"

namespace ht { namespace graphics { namespace ui {

	class Label : public GUIItem {
	private:
		utils::String text;
		maths::vec2 textPosition;

		enum Align {
			CENTER,
			LEFT,
			RIGHT
		} align = CENTER;

		unsigned int backgroundcolor = 0, forecolor = 0x000000FF;

		void(*onClick)(const utils::Event&) = [](const utils::Event& e) {};
		void(*onHover)(const utils::Event&) = [](const utils::Event& e) {};
		void(*onDrag)(const utils::Event&) = [](const utils::Event& e) {};

	public:

		Label(float x, float y, float width, float height, utils::String text);
		~Label() {}

		void update(const utils::Event& e) override;

		void onClick(void(*onClick)(const utils::Event&));

	protected:
		void getSize() {

		}

	};

} } }
