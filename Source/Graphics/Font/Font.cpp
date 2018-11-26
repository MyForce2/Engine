#include "Font.h"

namespace Engine {
	namespace Graphics {


		Font::Font(const std::string& fileName, unsigned int fontSize) : fileName(fileName), fontSize(fontSize) {
			init();
		}

		Font::~Font() {
			delete fontAtlas;
		}

		void Font::init() {
			Tg::FontDescription fontDescription(fileName, fontSize);
			Tg::FontGlyphRange glyphRange(GLYPH_SET_START, GLYPH_SET_END);
			font = Tg::BuildFont(fontDescription, glyphRange, FONT_BORDER);
			Tg::Image image = font.image;
			Tg::Size imageSize = image.GetSize();
			std::vector<unsigned char> RGBAData;
			convertToRGBA(image.GetImageBuffer(), RGBAData);
			fontAtlas = new Texture(RGBAData.data(), imageSize.width, imageSize.height, GL_RGBA8, GL_RGBA, GL_LINEAR);
		}

		void Font::convertToRGBA(const std::vector<unsigned char>& sourceData, std::vector<unsigned char>& outData) {
			for (const unsigned char& colorData : sourceData) {
				if (colorData == 255)
					for (int i = 0; i < 4; i++)
						outData.push_back(255);
				else
					for (int i = 0; i < 4; i++)
						outData.push_back(0);
			}
		}
	}
}