
#include "Camera.h"

namespace Engine {
	namespace Graphics {

		using namespace Math;
		const float Camera::sensitivity = 0.05f;

		Camera::Camera(const Window& window, float near, float far) : upDirection(0, 1, 0), yaw(0.f), pitch(0.f), windowSize(window.getSize()), near(near), far(far) {
			projection = Mat4::perspective(windowSize.x / windowSize.y, 45.f, near, far);
			view = generateViewMatrix();
		}

		Camera::~Camera() {

		}

		void Camera::setPosition(const Vec3& position) {
			this->position = position;
		}

		void Camera::setViewingDirection(const Vec3& direction) {
			this->viewingDirection = direction;
		}

		void Camera::update(const Window& window) {
			view = generateViewMatrix();
			viewingDirection = generateViewDirection(window);
			if (windowSize != window.getSize()) {
				windowSize = window.getSize();
				projection = Mat4::perspective(windowSize.x / windowSize.y, 45.f, near, far);
			}
		}

		Mat4 Camera::generateViewMatrix() const {
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
			view[3].x = (-x).dot(position);
			view[0].y = y.x;
			view[1].y = y.y;
			view[2].y = y.z;
			view[3].y = (-y).dot(position);
			view[0].z = z.x;
			view[1].z = z.y;
			view[2].z = z.z;
			view[3].z = (-z).dot(position);
			return view;
		}

		Math::Vec3 Camera::generateViewDirection(const Window& window) {
			Vec2 center = window.getSize() / 2;
			Vec2 mousePos = window.getMousePosition();
			Vec2 offset(mousePos.x - center.x, center.y - mousePos.y);
			if (offset == Vec2(0, 0))
				return viewingDirection;
			offset *= sensitivity;
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
			window.setMousePosition(center);
			return newView;
		}
	}
}