
#include "Camera.h"

namespace Engine {
	namespace Graphics {

		using namespace Math;
		const float Camera::MAX_PITCH_ANGLE = 89.f;
		const float Camera::SENSITIVITY = 0.05f;
		const float Camera::FIELD_OF_VIEW = 45.f;
		const float Camera::MOVEMENT_SPEED = 10.f;
		const float Camera::SPEED_BOOST = 5.f;

		Camera::Camera(const Window& window, float near, float far) : upDirection(0, 1, 0), yaw(0.f), pitch(0.f), windowSize(window.getSize()), near(near), far(far) {
			projection = Mat4::perspective(windowSize.x / windowSize.y, FIELD_OF_VIEW, near, far);
			view = generateViewMatrix();
			viewFrustum.setNearFarData(FIELD_OF_VIEW, 16.0f / 9.0f, near, far);
		}

		Camera::~Camera() {

		}

		void Camera::setPosition(const Vec3& position) {
			this->position = position;
		}

		void Camera::setViewingDirection(const Vec3& direction) {
			this->viewingDirection = direction;
		}

		void Camera::update(const Window& window, float time) {
			view = generateViewMatrix();
			viewingDirection = generateViewDirection(window);
			if (windowSize != window.getSize()) {
				std::cout << "Change" << std::endl;
				windowSize = window.getSize();
				projection = Mat4::perspective(windowSize.x / windowSize.y, 45.f, near, far);
				glViewport(0, 0, int(windowSize.x), int(windowSize.y));
			}
			float distance = time * MOVEMENT_SPEED;
			Vec3 strafeAxis = viewingDirection.cross(upDirection);
			strafeAxis.normalize();
			if (window.isKeyPressed(GLFW_KEY_SPACE))
				distance *= SPEED_BOOST;
			if (window.isKeyPressed(GLFW_KEY_W))
				position += viewingDirection * distance;
			if (window.isKeyPressed(GLFW_KEY_S))
				position -= viewingDirection * distance;
			if (window.isKeyPressed(GLFW_KEY_A))
				position -= strafeAxis * distance;
			if (window.isKeyPressed(GLFW_KEY_D))
				position += strafeAxis * distance;
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
			viewFrustum.generatePlanes(position, x, y, z, near, far);
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
			offset *= SENSITIVITY;
			yaw += offset.x;
			pitch += offset.y;
			if (pitch > MAX_PITCH_ANGLE)
				pitch = MAX_PITCH_ANGLE;
			if (pitch < -MAX_PITCH_ANGLE)
				pitch = -MAX_PITCH_ANGLE;
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