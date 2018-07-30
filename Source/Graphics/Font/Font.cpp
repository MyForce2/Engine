#include "Font.h"

namespace Engine {
	namespace Graphics {


		Font::Font(const std::string& fileName, unsigned int fontSize) : fileName(fileName), fontSize(fontSize) {
			Tg::FontDescription fontDescription(fileName, fontSize);
			Tg::FontGlyphRange glyphRange(GLYPH_SET_START, GLYPH_SET_END);
			font = Tg::BuildFont(fontDescription, glyphRange, FONT_BORDER);
			Tg::Image image = font.image;
			Tg::Size imageSize = image.GetSize();
			fontAtlas = new Texture(image.GetImageBuffer().data(), imageSize.width, imageSize.height, GL_RED, GL_RED, GL_LINEAR);
		}

		Font::~Font() {
			delete fontAtlas;
		}
	}
}