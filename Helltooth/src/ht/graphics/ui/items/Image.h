#pragma once

#include "../GUIItem.h"

#include "graphics/textures/Texture.h"
#include "graphics/textures/TextureManager.h"

namespace ht { namespace graphics { namespace ui {

	class Image : public GUIItem {
	private:
		maths::vec2 size;

		const Texture* texture;

		Sprite* image = nullptr;

	public:
		Image(const Texture* texture, const f32 &x, const f32 &y, const f32 &width, const f32 &height);
		Image(uint32 &textureID, const f32 &x, const f32 &y, const f32 &width, const f32 &height);

		__forceinline ~Image() { if(image) del image; }

		__forceinline void changeTexture(const Texture* texture) { this->texture = texture; updateSprite(); }

		__forceinline void changeTexture(unsigned int textureID) { const Texture* texture = TextureManager::Get()->getTexture(textureID); changeTexture(texture); }

	private:
		void updateSprite();
	};

} } }
