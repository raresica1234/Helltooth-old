#include "FontManager.h"

namespace ht { namespace graphics {
	using namespace utils;
	using namespace maths;

	FontManager* FontManager::manager = nullptr;


	FontManager::FontManager() {
		FT_Error error = FT_Init_FreeType(&library);

		if (error) {
			HT_FATAL("[FontManager] An error occurred when initializing FreeType!");
		}
	}

	FontManager::~FontManager() {
		for (auto entry : fonts)
			del entry.second.texture;
		
		FT_Done_FreeType(library);
	}

	void FontManager::selectFont(utils::String identifier) {
		selected = fonts[identifier];
	}

	void FontManager::addFont(String path, String identifier, unsigned int size) {
		String realPath;
		VFS::resolvePhysicalPath(path, realPath);
		FT_Face face;
		FT_Error error = FT_New_Face(library, realPath.c_str(), 0, &face);

		HT_MSG("[FontManager] Font %s loaded!", face->family_name);

		if (error == FT_Err_Unknown_File_Format) {
			HT_FATAL("[FontManager] Font format not supported!");
		}
		else if (error) {
			HT_FATAL("[FontManager] An error occurred when loading the font");
		}

		std::unordered_map<unsigned int, Glyph> charMap;

		//do something with those numChars

		unsigned int segmentWidth = 0;
		unsigned int segmentHeight = 0;


		char start = 0x21;
		char end = 0x7E;

		unsigned int numCharacters = end - start;

		Font& font = fonts[identifier];

		FT_Set_Pixel_Sizes(face, size, size);
		FT_Select_Charmap(face, FT_ENCODING_UNICODE);

		for (char i = start; i < end; i++) {
			unsigned int id = FT_Get_Char_Index(face, i);

			FT_Load_Glyph(face, id, 0);
			FT_GlyphSlot gs = face->glyph;

			FT_Render_Glyph(gs, FT_RENDER_MODE_NORMAL);
			FT_Bitmap bitmap = gs->bitmap;
			
			FT_Glyph_Metrics metrics = gs->metrics;

			Glyph glyph;
		
			glyph.unicodeCharacter = i;
			glyph.advance.x = gs->advance.x >> 6;
			glyph.offset.x = metrics.horiBearingX >> 6;
			glyph.offset.y = (metrics.horiBearingY >> 6) - (metrics.height >> 6);
			glyph.bitmapSize.x = bitmap.width;
			glyph.bitmapSize.y = bitmap.rows;

			unsigned int bitmap_size = bitmap.rows * bitmap.width;

			glyph.bitmap = htnew unsigned char[bitmap_size];
			memcpy(glyph.bitmap, gs->bitmap.buffer, bitmap_size);

			if (glyph.bitmapSize.x > segmentWidth)  segmentWidth = glyph.bitmapSize.x;
			if (glyph.bitmapSize.y > segmentHeight) segmentHeight = glyph.bitmapSize.y;

			charMap[i] = glyph;
		}

		unsigned int bitmapSquareSize = (unsigned int)ceilf(sqrtf((float)numCharacters));
		unsigned int bitmapWidth = bitmapSquareSize * segmentWidth;
		unsigned int bitmapHeight = bitmapSquareSize * segmentHeight;

		unsigned char* bitmapData = new unsigned char[bitmapWidth * bitmapHeight];
		memset(bitmapData, 0, bitmapWidth * bitmapHeight);

		float xStep = (float)segmentWidth / (float)bitmapWidth;
		float yStep = (float)segmentHeight / (float)bitmapHeight;

		unsigned int currentGlyph = 0;

		for (char i = start; i < end; i++) {
			Glyph glyph = charMap[i];

			int xStart = currentGlyph % bitmapSquareSize;
			int yStart = currentGlyph / bitmapSquareSize;

			glyph.uv.x = (float)xStart * xStep;
			glyph.uv.y = (float)yStart * yStep;
			glyph.uv.z = glyph.uv.x + xStep;
			glyph.uv.w = glyph.uv.y + yStep;

			font.glyphs[i] = glyph;

			unsigned int yOffset = segmentHeight - glyph.bitmapSize.y;

			for (int y = 0; y < glyph.bitmapSize.y; y++) {
				int ya = (yStart * segmentHeight) + y + yOffset;
				for (int x = 0; x < glyph.bitmapSize.x; x++) {
					int xa = (xStart * segmentWidth) + x;
					bitmapData[xa + ya * bitmapWidth] = glyph.bitmap[x + y * (int)glyph.bitmapSize.x];
				}
			}

			currentGlyph++;
			del[] glyph.bitmap;
		}

		font.texture = htnew Texture();
		font.size = size;
		font.texture->loadPixelArray(bitmapData, bitmapWidth, bitmapHeight, 8, GL_CLAMP_TO_BORDER);
		selectFont(identifier);
	}

} }
