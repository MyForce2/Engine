#pragma once

#include <Typo/Typo.h>
#include "Graphics/Textures/Texture.h"

namespace Engine {
	namespace Graphics {


		class Font {
		private:
			const std::string fileName;
			const unsigned int fontSize;
			const Texture* fontAtlas;
			Tg::FontModel font;

			static const wchar_t GLYPH_SET_START = wchar_t(31);
			static const wchar_t GLYPH_SET_END = wchar_t(126);
			static const unsigned int FONT_BORDER = 3U;

		public:
			Font(const std::string& fileName, unsigned int fontSize);
			Font(const Font& font);
			~Font();

			inline const Texture& getFontAtlas() const { return *fontAtlas; }
			inline const Tg::FontModel& getFont() const { return font; }
			inline unsigned int getFontSize() const { return fontSize; }

		private:
			void init();
		};
	}
}
