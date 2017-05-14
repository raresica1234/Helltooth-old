#include "Image.h"

namespace ht { namespace graphics { namespace ui {
	using namespace maths;
	using namespace utils;
	
	Image::Image(const Texture* texture, const f32 &x, const f32 &y, const f32 &width, const f32 &height)
		: GUIItem(x,y,width,height), texture(texture), size(width,height) {
		updateSprite();
	}

	Image::Image(uint32 &textureID, const f32 &x, const f32 &y, const f32 &width, const f32 &height)
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
