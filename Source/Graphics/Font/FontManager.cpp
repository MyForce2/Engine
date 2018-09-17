#include "FontManager.h"


namespace Engine {
	namespace Graphics {

		FontManager* FontManager::instance = nullptr;

		FontManager::~FontManager() {
			for (Font* font : fonts)
				delete font;
		}

		FontManager* FontManager::getFontManager() {
			if (instance == nullptr)
				instance = new FontManager();
			return instance;
		}

		void FontManager::deleteManager() {
			delete instance;
		}

		bool FontManager::hasFont(const std::string& name, size_t pointSize) const {
			return get(name, pointSize) != nullptr;
		}

		Font* FontManager::get(const std::string& name, size_t pointSize) const {
			for (Font* font : fonts) {
				if (font->getFileName() == name && font->getFontSize() == pointSize)
					return font;
			}
			return nullptr;
		}

		void FontManager::add(const std::string& name, size_t pointSize) {
			if (!hasFont(name, pointSize))
				fonts.push_back(new Font(name, pointSize));
		}
	}
}