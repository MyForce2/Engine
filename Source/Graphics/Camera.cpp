
#include "Camera.h"

namespace Engine {
	namespace Graphics {

		using namespace Math;

		Camera::Camera() : upDirection(0, 1, 0), yaw(-90.f), pitch(0.f) {

		}

		Camera::~Camera() {

		}

		void Camera::setPosition(const Vec3& position) {
			this->position = position;
		}

		void Camera::setViewingDirection(const Vec3& direction) {
			this->viewingDirection = direction;
		}

		Mat4 Camera::generateViewMatrix() {
			Mat4 view(1.f);
			Vec3 x, y, z;
			Vec3 v = position + viewingDirection;
			z = position - v;
			z.normalize();
			y = upDirection;
			x = y.cross(z);
			y = z.cross(x);
			x.normalize();
			y.normalize();
			view[0].x = x.x;
			view[1].x = x.y;
			view[2].x = x.z;
			view[3].x = (x * -1).dot(position);
			view[0].y = y.x;
			view[1].y = y.y;
			view[2].y = y.z;
			view[3].y = (y * -1).dot(position);
			view[0].z = z.x;
			view[1].z = z.y;
			view[2].z = z.z;
			view[3].z = (z * -1).dot(position);
			return view;
		}

		void Camera::updateViewDirection(const Window& window) {
			Vec2 center = window.getSize() / 2;
			Vec2 mousePos = window.getMousePosition();
			Vec2 offset(mousePos.x - center.x, center.y - mousePos.y);
			float sense = 0.05f;
			offset *= sense;
			yaw += offset.x;
			pitch += offset.y;
			if (pitch > 89.f)
				pitch = 89.f;
			if (pitch < -89.f)
				pitch = -89.f;
			Vec3 newView;
			float yawRad = toRadians(yaw);
			float pitchRad = toRadians(pitch);
			newView.x = std::cos(yawRad) * std::cos(pitchRad);
			newView.y = std::sin(pitchRad);
			newView.z = std::sin(yawRad) * std::cos(pitchRad);
			newView.normalize();
			viewingDirection = newView;
			window.setMousePosition(center);
		}
	}
}