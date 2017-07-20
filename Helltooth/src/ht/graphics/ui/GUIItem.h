#pragma once

#include <vector>

#include "../rendering/2D/Sprite.h"
#include "../rendering/renderers/2D/BatchRenderer2D.h"

#include "maths/mat3.h"

#include "utils/input/Input.h"

namespace ht { namespace graphics { namespace ui {

	class GUIItem {
	protected:
		std::vector<Sprite*> sprites;
		maths::mat4 transformation;

		maths::vec4 size;

		bool visible = true;

		void(*f_OnClick)(const utils::Event&, GUIItem* item) = [](const utils::Event& e, GUIItem* item) {};
		void(*f_OnHover)(const utils::Event&, GUIItem* item) = [](const utils::Event& e, GUIItem* item) {};
		void(*f_OnDrag)(const utils::Event&, GUIItem* item) = [](const utils::Event& e, GUIItem* item) {};

	public:
		GUIItem(const f32& x, const f32& y, const f32& width, const f32& height)
			: size(x, y, width, height) {
			transformation.translate(x, y, 0);
		}

		virtual ~GUIItem() {
			for (Sprite* sprite : sprites)
				del sprite;
		}

		virtual void submit(BatchRenderer2D* renderer) {
			if (!visible) return;

			renderer->push(transformation);
			for (Sprite* sprite : sprites) {
				renderer->submit(sprite);
			}

			renderer->pop();
		}

		virtual void update(const utils::Event &e) {
			if (e.handled)
				return;

			float my = e.mouseY;
			float mx = e.mouseX;

			if (mx >= size.x && mx <= (size.x +size.z) && my >= size.y && my <= (size.y + size.w)) {
				f_OnHover(e, this);
				for (unsigned int i = 0; i < MAX_BUTTONS; i++)
					if (e.mouse_buttons[i]) {
						f_OnClick(e, this);
						f_OnDrag(e, this);
					}
				e.handled = true;
			}
		}
		
		__forceinline void onClick(void(*f_onClick)(const utils::Event&, GUIItem* item)) {
			this->f_OnClick = f_onClick;
		}

		__forceinline void onHover(void(*f_onHover)(const utils::Event&, GUIItem* item)) {
			this->f_OnHover = f_onHover;
		}

		__forceinline void onDrag(void(*f_onDrag)(const utils::Event&, GUIItem* item)) {
			this->f_OnDrag = f_onDrag;
		}

	protected:
		virtual void addSprite(Sprite* sprite) { sprites.push_back(sprite); }

	};

} } }