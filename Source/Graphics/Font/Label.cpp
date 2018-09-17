#include "Label.h"

namespace Engine {
	namespace Graphics {

		using namespace Math;

		Label::Label(const std::string& text, const Font* font) : text(text), startPosition(), labelColor(255.f), 
			font(font) {

		}

		Label::Label(const std::string& text, const Vec2& startPosition, const Font* font) : text(text), startPosition(startPosition),
			labelColor(255.f), font(font) {

		}

		Label::Label(const std::string& text, const Vec2& startPosition, const Vec3& labelColor, const Font* font) 
			: text(text), startPosition(startPosition), labelColor(labelColor), font(font) {

		}

		Label::Label() : text(), startPosition(), labelColor(255.f) {

		}

		Label::~Label() {

		}

		void Label::setText(const std::string& text) {
			this->text = text;
		}

		void Label::setStartPosition(const Vec2& startPosition) {
			this->startPosition = startPosition;
		}

		void Label::setLabelColor(const Vec3& labelColor) {
			this->labelColor = labelColor;
		}

		void Label::generateVerticesData() {
			using namespace Tg;
			const FontModel font = this->font->getFont();
			float imageHeight = float(font.image.GetSize().height);
			float imageWidth = float(font.image.GetSize().width);
			Vec3 normalizedColor = labelColor / 255;
			Vec3 position(startPosition);

			for (unsigned int i = 0; i < text.length(); i++) {
				FontGlyph glyph = font.glyphSet[text[i]];
				Vec2 topRightUV = Vec2(glyph.rect.right / imageWidth, glyph.rect.top / imageHeight);
				Vec2 bottomLeftUV = Vec2(glyph.rect.left / imageWidth, glyph.rect.bottom / imageHeight);
				float yOffset = (glyph.height - glyph.yOffset);
				float width = glyph.width;
				float height = glyph.height;

				// Top right

				vertices.push_back(Vec2(position.x + width, position.y + height - yOffset));
				vertices.push_back(Vec2(topRightUV.x, topRightUV.y));
				vertices.push_back(normalizedColor);

				// Top left

				vertices.push_back(Vec2(position.x, position.y + height - yOffset));
				vertices.push_back(Vec2(bottomLeftUV.x, topRightUV.y));
				vertices.push_back(normalizedColor);

				// Bottom left

				vertices.push_back(Vec2(position.x, position.y - yOffset));
				vertices.push_back(Vec2(bottomLeftUV.x, bottomLeftUV.y));
				vertices.push_back(normalizedColor);

				// Bottom right

				vertices.push_back(Vec2(position.x + width, position.y - yOffset));
				vertices.push_back(Vec2(topRightUV.x, bottomLeftUV.y));
				vertices.push_back(normalizedColor);
			}
		}

	}
}