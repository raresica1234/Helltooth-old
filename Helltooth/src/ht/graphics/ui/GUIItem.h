#pragma once

#include <vector>

#include "../rendering/2D/Sprite.h"

namespace ht { namespace graphics { namespace ui {

	class GUIItem {
	protected:
		std::vector<Sprite*> sprites;
		maths::mat3 transformation;

		bool visible = true;

	public:
		GUIItem(maths::vec2 position) {
			GUIItem(position.x, position.y);
		}

		GUIItem(const float x, const float y) {
			transformation = maths::mat3();
			transformation.translate(x, y);
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

		//virtual void update(Event &e) = 0;

	protected:
		virtual void addSprite(Sprite* sprite) {}

	};


} } }
