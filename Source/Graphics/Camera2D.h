#pragma once

#include "Math\Mat4.h"
#include "Math\Vec2.h"
#include "Math\Vec3.h"
#include "Utils\Clock.h"
#include "Window.h"

namespace Engine {
	namespace Graphics {

		class Camera2D {
		private:
			Math::Mat4 viewMatrix;
			Math::Mat4 projection;
			Math::Vec2 center;

		public:
			Camera2D(const Window& window);
			~Camera2D();

			void setCenter(const Math::Vec2& centerPosition);
			void move(const Math::Vec3& translation);

			inline const Math::Mat4& getView() const { return viewMatrix; }
			inline const Math::Mat4& getProjection() const { return projection; }
		};
	}
}
