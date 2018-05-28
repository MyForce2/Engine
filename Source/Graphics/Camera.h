#pragma once

#include "Math\Mat4.h"
#include "Math\Vec3.h"
#include "Window.h"
#include "Utils\Clock.h"

namespace Engine {
	namespace Graphics {

		class Camera {
		private:
			Math::Vec3 position;
			Math::Vec3 viewingDirection;
			Math::Vec3 upDirection;
			float pitch;
			float yaw;

		public:
			Camera();
			~Camera();

			void setPosition(const Math::Vec3& position);
			void setViewingDirection(const Math::Vec3& direction);
			inline const Math::Vec3& getPosition() const { return position; }
			inline const Math::Vec3& getViewingDirection() const { return viewingDirection; }

			Math::Mat4 generateViewMatrix();
			void updateViewDirection(const Window& window);
		};
	}
}
