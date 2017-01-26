#pragma once

#include <unordered_map>

#include <freetype-gl.h>
#include <texture-atlas.h>
#include <texture-font.h>

#include "graphics/textures/Texture.h"
#include "graphics/window/WindowManager.h"

#include "maths/vec2.h"
#include "maths/vec4.h"

#include "tools/VFS/VFS.h"

#include "utils/memory/MemoryManager.h"
#include "utils/String.h"

namespace ht { namespace graphics {

	struct Glyph {
		char unicodeCharacter;
		maths::vec2 advance;
		maths::vec2 offset;
		maths::vec2 bitmapSize;

		float u0, v0, u1, v1;

		unsigned char* bitmap = nullptr;
	};

	struct Font {
		ftgl::texture_font_t* font;
		ftgl::texture_atlas_t* atlas;
		maths::vec2 scale;
		float size;

		Font() {
			scale.x = 1;
			scale.y = 1;
		}
	};

	class FontManager {
	private:
		std::unordered_map<utils::String, Font> fonts;
		Font selected;
		
		static FontManager* manager;


	private:
		FontManager();
		~FontManager();

	public:
		void addFont(utils::String path, utils::String identifier, float size);

		void selectFont(utils::String identifier);


		__forceinline Font getFont() { return selected; }


		__forceinline static void Init() {
			if (!manager)
				manager = htnew FontManager();
			else
				HT_WARN("[FontManager] Font Manager already initialized!");
		}

		__forceinline static FontManager* Get() {
			if (!manager)
				Init();
			return manager;
		}

		__forceinline static void End() {
			if (manager) {
				del manager;
				manager = nullptr;
			}
			else
				HT_WARN("[FontManager] Font Manager not initialized!");
		}

	};


} }
