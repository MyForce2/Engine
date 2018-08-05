#include "Label.h"

namespace Engine {
	namespace Graphics {

		using namespace Math;

		Label::Label(const std::string& text) : text(text), startPosition(), labelColor(255.f), model(1.f) {

		}

		Label::Label(const std::string& text, const Vec2& startPosition) : text(text), startPosition(startPosition), 
			labelColor(255.f), model(1.f) {

		}

		Label::Label(const std::string& text, const Vec2& startPosition, const Vec3& labelColor) :text(text), 
			startPosition(startPosition), labelColor(labelColor), model(1.f) {

		}

		Label::Label() : text(), startPosition(), labelColor(255.f), model(1.f) {

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

		void Label::setModelMatrix(const Mat4& model) {
			this->model = model;
		}

		void Label::scale(const Vec2& scale) {
			model = Mat4::translation(-startPosition) * model;
			model = Mat4::scale(scale) * model;
			model = Mat4::translation(startPosition) * model;
		}

		void Label::rotate(float angle) {
			float rad = toRadians(angle);
			model = Mat4::translation(-startPosition) * model;
			model = Mat4::rotationZ(rad) * model;
			model = Mat4::translation(startPosition) * model;
		}
	}
}