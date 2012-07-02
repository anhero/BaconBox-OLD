#include "BaconBox/Display/Text/FreetypeImplementation/FontImplementation.h"
#include <sstream>
#include <freetype/ftglyph.h>
#include <algorithm>

#include "BaconBox/Console.h"
#include "BaconBox/ResourceManager.h"
#include "BaconBox/Helper/MathHelper.h"
#include "BaconBox/Helper/Parser.h"
#include "BaconBox/Helper/DeleteHelper.h"

namespace BaconBox {
	FT_Library FontImplementation::fontRenderer = NULL;


	void FontImplementation::initializeFontRenderer() {
		if (FT_Init_FreeType(&fontRenderer)) {
			Console::println("Can not load freetype");
		}
	}

	const std::string &FontImplementation::getName() const {
		return name;
	}

	FontImplementation::FontImplementation(const std::string &newName,
	                                       const std::string &newPath) :
		name(newName), size(), font(), automaticLineHeight(true), lineHeight(0),
		texturesKey(), glyphCache() {

		// We load the font face
		int error = FT_New_Face(fontRenderer, newPath.c_str(), 0, &font);

		if (error == FT_Err_Unknown_File_Format) {
			Console::println("Can't load font, unknow font file format");

		} else if (error) {
			Console::println("Can't load font, unknow error");
		}

		setPixelSize(30);
	}

	FontImplementation::~FontImplementation() {
		for (GlyphCache::iterator i = glyphCache.begin(); i != glyphCache.end();
		     ++i) {
			std::for_each(i->second.begin(), i->second.end(), DeletePointerFromPair());
		}
	}

	const GlyphInformation *FontImplementation::getGlyphInformation(Char32 unicodeValue) {
		GlyphCache::iterator i = glyphCache.find(size);
		GlyphInformation *result;
		bool glyphCached = false;

		//we check if the glyph is already loaded and cached.
		if (i != glyphCache.end()) {
			GlyphCache::mapped_type::const_iterator j = i->second.find(unicodeValue);

			if (j != i->second.end()) {
				result = j->second;
				glyphCached = true;
			}
		}

		//If the glyph is not already cached
		if (glyphCached == false) {
			FT_UInt glyph_index;
			//We ask the font face what is the glyph index for the given unicode value
			glyph_index = FT_Get_Char_Index(font, unicodeValue);

			//we load the glyph
			if (FT_Load_Glyph(font, glyph_index, FT_LOAD_RENDER)) {
				Console::println("Can't load glyph");
			}

			FT_Glyph currentGlyph;

			if (FT_Get_Glyph(font->glyph,  &currentGlyph)) {
				Console::println("Can't extract glyph from freetype glyph slot");
			}

			FT_BitmapGlyph currentBitmapGlyph = (FT_BitmapGlyph)currentGlyph;

			// We save the size of the glyph
			int glyphWidth = font->glyph->bitmap.width;
			int glyphHeight = font->glyph->bitmap.rows;

			result = new GlyphInformation();
			std::stringstream key;
			key << name << "-" << size << "-" << unicodeValue;

			//PixMap *glyphPixMap = new PixMap(currentBitmapGlyph->bitmap.buffer, glyphWidth, glyphHeight, ColorFormat::ALPHA);
			PixMap *glyphPixMap = new PixMap(glyphWidth + 2, glyphHeight + 2, 0, ColorFormat::ALPHA);
			glyphPixMap->insertSubPixMap(currentBitmapGlyph->bitmap.buffer, glyphWidth, glyphHeight, 1, 1);
			result->textureInformation = ResourceManager::addTexture(key.str(), glyphPixMap);
			result->advance.x = static_cast<float>(font->glyph->advance.x >> 6);

			result->size.x = static_cast<float>(glyphWidth);
			result->size.y = static_cast<float>(glyphHeight);

			result->horizontalBearing.x = static_cast<float>(font->glyph->bitmap_left);
			result->horizontalBearing.y = static_cast<float>(font->glyph->bitmap_top);

			i = glyphCache.insert(std::make_pair(size, GlyphCache::mapped_type())).first;

			i->second.insert(std::make_pair(unicodeValue, result));
			FT_Done_Glyph(currentGlyph);
		}

		return result;
	}

	void FontImplementation::setPixelSize(int pixelSize) {
		if (FT_Set_Pixel_Sizes(font, 0, pixelSize)) {
			Console::println("Can't set pixel size.");
		}

		(size = Parser::intToString(pixelSize)).append("px");
	}

	void FontImplementation::setPointSize(int pointSize, int dpi) {
		if (FT_Set_Char_Size(font, 0, pointSize * 64, dpi, dpi)) {
			Console::println("Can't set point size");
		}

		(size = Parser::intToString(pointSize)).append("pt");
	}

	void FontImplementation::setManualLineHeight(int newLineHeight) {
		lineHeight = newLineHeight;
		automaticLineHeight = false;
	}

	int FontImplementation::getLineHeight() const {
		if (automaticLineHeight) {
			return  font->size->metrics.height >> 6;

		} else {
			return lineHeight;
		}
	}

	void FontImplementation::setAutomaticLineHeight() {
		automaticLineHeight = true;
	}
}
