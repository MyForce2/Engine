
#include "Camera.h"

namespace Engine {
	namespace Graphics {

		using namespace Math;

		Camera::Camera() : upDirection(0, 1, 0) {

		}

		Camera::~Camera() {

		}

		void Camera::setPosition(const Vec3& position) {
			this->position = position;
		}

		void Camera::setViewingDirection(const Vec3& direction) {
			this->viewingDirection = direction;
		}

		Mat4 Camera::generateViewMatrix() const {
			Mat4 view(1.f);
			Vec3 x, y, z;
			z = position - viewingDirection;
			z.normalize();
			y = upDirection;
			x = y.cross(z);
			y = z.cross(x);
			x.normalize();
			y.normalize();
			view[0].x = x.x;
			view[0].y = y.x;
			view[0].z = z.x;
			view[1].x = x.y;
			view[1].y = y.y;
			view[1].z = z.y;
			view[2].x = x.z;
			view[2].y = y.z;
			view[2].z = z.z;
			view[3].x = (x * -1).dot(position);
			view[3].y = (y * -1).dot(position);
			view[3].z = (z * -1).dot(position);
			return view;
		}
	}
}