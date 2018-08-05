#pragma once

#include <string>
#include "Math\Vectors\Vec2.h"
#include "Math\Vectors\Vec3.h"
#include "Math/Mat4.h"

namespace Engine {
	namespace Graphics {

		/*
		A class that holds the data for a 2d text label
		*/
		class Label {
		private:
			std::string text;
			Math::Vec2 startPosition;
			Math::Vec3 labelColor;
			Math::Mat4 model;

		public:
			Label(const std::string& text);
			Label(const std::string& text, const Math::Vec2& startPosition);
			Label(const std::string& text, const Math::Vec2& startPosition, const Math::Vec3& labelColor);
			Label();

			~Label();

			inline const std::string& getText() const { return text; }
			inline const Math::Vec2& getStartPosition() const { return startPosition; }
			inline const Math::Vec3& getLabelColor() const { return labelColor; }
			inline const Math::Mat4& getModelMatrix() const { return model; }

			void setText(const std::string& text);
			void setStartPosition(const Math::Vec2& startPosition);
			void setLabelColor(const Math::Vec3& labelColor);
			void setModelMatrix(const Math::Mat4& model);

			void scale(const Math::Vec2& scale);
			void rotate(float angle);

		};
	}
}
