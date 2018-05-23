#pragma once

#include "Math\Mat4.h"
#include "Math\Vec3.h"


namespace Engine {
	namespace Graphics {

		class Camera {
		private:
			Math::Vec3 position;
			Math::Vec3 viewingDirection;
			Math::Vec3 upDirection;

		public:
			Camera();
			~Camera();

			void setPosition(const Math::Vec3& position);
			void setViewingDirection(const Math::Vec3& direction);

			Math::Mat4 generateViewMatrix() const;
		};
	}
}
