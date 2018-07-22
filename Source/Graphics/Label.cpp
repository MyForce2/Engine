#include "Label.h"

namespace Engine {
	namespace Graphics {

		Label::Label(const std::string& text, unsigned short fontSize) : text(text), fontSize(fontSize), startPosition(), labelColor(1.f) {

		}

		Label::Label(const std::string& text, unsigned short fontSize, const Math::Vec2& startPosition) : text(text), fontSize(fontSize),
			startPosition(startPosition), labelColor(1.f) {

		}

		Label::Label(const std::string& text, unsigned short fontSize, const Math::Vec2& startPosition, const Math::Vec3& labelColor) :
			text(text), fontSize(fontSize), startPosition(startPosition), labelColor(labelColor) {

		}

		Label::Label() : text(), fontSize(), startPosition(), labelColor(1.f) {

		}

		Label::~Label() {

		}

		void Label::setText(const std::string& text) {
			this->text = text;
		}

		void Label::setFontSize(unsigned short fontSize) {
			this->fontSize = fontSize;
		}

		void Label::setStartPosition(const Math::Vec2& startPosition) {
			this->startPosition = startPosition;
		}

		void Label::setLabelColor(const Math::Vec3& labelColor) {
			this->labelColor = labelColor;
		}
	}
}