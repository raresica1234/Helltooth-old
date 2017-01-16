#pragma once

#include <vector>

#include "../rendering/2D/Sprite.h"

namespace ht { namespace graphics {

	class GUIItem {
	protected:
		std::vector<Sprite> sprites;
	public:
		GUIItem() {}
		~GUIItem() {}

		virtual void render() = 0;

		//Event& e
		virtual void update() = 0;
	};


} }
