#include "Image.h"

namespace ht { namespace graphics { namespace ui {
	using namespace maths;
	using namespace utils;
	
	Image::Image(const Texture* texture, const float x, const float y, const float width, const float height)
		: GUIItem(x,y,width,height), texture(texture), size(width,height) {
		updateSprite();
	}

	Image::Image(unsigned int textureID, const float x, const float y, const float width, const float height)
		: Image(TextureManager::Get()->getTexture(textureID), x, y, width, height) {
	}

	void Image::updateSprite() {
		if (sprites.empty()) {
			image = htnew Sprite(0, 0, size.x, size.y);
			sprites.push_back(image);
		}
		image->setTexture(texture);
	}

} } }
