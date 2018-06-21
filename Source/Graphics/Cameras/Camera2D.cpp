

#include "Camera2D.h"



namespace Engine {
	namespace Graphics {

		using namespace Math;

		Camera2D::Camera2D(const Window& window) : viewMatrix(1.f), projection() {
			Vec2 size = window.getSize();
			projection = Mat4::orthographic(0.f, size.x, 0.f, size.y, -1.f, 1.f);
		}

		Camera2D::~Camera2D() {
		
		}

		void Camera2D::setCenter(const Vec2& centerPosition) {
			center = centerPosition;
		}

		void Camera2D::move(const Vec3& translation) {
			viewMatrix = Mat4::translation(translation) * viewMatrix;
		}
	}
}