#include "FontManager.h"

#include <FreeImage/FreeImage.h>

#define FONT_TEXTURE_SIZE 512

namespace ht { namespace graphics {
	using namespace utils;
	using namespace maths;

	FontManager* FontManager::manager = nullptr;


	FontManager::FontManager() {
	}

	FontManager::~FontManager() {
		for (auto entry : fonts) {
			ftgl::texture_atlas_delete(entry.second.atlas);
			ftgl::texture_font_delete(entry.second.font);
		}
	}

	void FontManager::selectFont(utils::String identifier) {
		selected = fonts[identifier];
	}

	void FontManager::addFont(String path, String identifier, float size) {
		String realPath;
		VFS::resolvePhysicalPath(path, realPath);
		
		Font f = Font();
		f.atlas = ftgl::texture_atlas_new(FONT_TEXTURE_SIZE, FONT_TEXTURE_SIZE, 2);
		f.font = ftgl::texture_font_new_from_file(f.atlas, size, realPath.c_str());

		f.size = size;
		fonts[identifier] = f;

		selectFont(identifier);
	}

} }
