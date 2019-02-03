#include "ViewFrustum.h"
#include "Mat4.h"

namespace Engine {
	namespace Math {

		ViewFrustum::ViewFrustum() {

		}

		void ViewFrustum::setNearFarData(float fovAngle, float ratio, float nearDistance, float farDistance) {
			float t = std::tan(toRadians(fovAngle) * 0.5);
			nearPlaneHeight = nearDistance * t;
			nearPlaneWidth = nearPlaneHeight * ratio;
			farPlaneHeight = farDistance * t;
			farPlaneWidth = farPlaneHeight * ratio;
		}

		void ViewFrustum::generatePlanes(const Vec3 & position, const Vec3 & x, const Vec3 & y, const Vec3 & z, float nearDistance, float farDistance) {
			// Calculating the near and far plane centers
			Vec3 nearPlaneCenter = position - z * nearDistance;
			Vec3 farPlaneCenter = position - z * farDistance;
			// Calculating the near plane vertices
			Vec3 nearTopLeft = nearPlaneCenter + y * nearPlaneHeight - x * nearPlaneWidth;
			Vec3 nearTopRight = nearPlaneCenter + y * nearPlaneHeight + x * nearPlaneWidth;
			Vec3 nearBotLeft = nearPlaneCenter - y * nearPlaneHeight - x * nearPlaneWidth;
			Vec3 nearBotRight = nearPlaneCenter - y * nearPlaneHeight + x * nearPlaneWidth;

			nearPoints[0] = nearTopRight;
			nearPoints[1] = nearTopLeft;
			nearPoints[2] = nearBotLeft;
			nearPoints[3] = nearBotRight;

			// Calculating the far plane vertices
			Vec3 farTopLeft = farPlaneCenter + y * farPlaneHeight - x * farPlaneWidth;
			Vec3 farTopRight = farPlaneCenter + y * farPlaneHeight + x * farPlaneWidth;
			Vec3 farBotLeft = farPlaneCenter - y * farPlaneHeight - x * farPlaneWidth;
			Vec3 farBotRight = farPlaneCenter - y * farPlaneHeight + x * farPlaneWidth;

			farPoints[0] = farTopRight;
			farPoints[1] = farTopLeft;
			farPoints[2] = farBotLeft;
			farPoints[3] = farBotRight;

			// Set the frustum's planes
			planes.push_back(Plane(nearTopRight, nearTopLeft, farTopLeft));
			planes.push_back(Plane(nearBotLeft, nearBotRight, farBotRight));
			planes.push_back(Plane(nearTopLeft, nearBotLeft, farBotRight));
			planes.push_back(Plane(nearBotRight, nearTopRight, farBotRight));
			planes.push_back(Plane(nearTopLeft, nearTopRight, nearBotRight));
			planes.push_back(Plane(farTopRight, farTopLeft, farBotLeft));
		}

		bool ViewFrustum::pointInFrustum(const Vec3& point) const {
			for (const Plane& plane : planes) {
				if (plane.distance(point) < 0)
					return false;
			}
			return true;
		}

		bool ViewFrustum::boxInFrustum(const AABB& box) const {
			const std::array<Vec3, 8>& vertices = box.getVertices();
			for (const Vec3& vertex : vertices) {
				if (!pointInFrustum(vertex))
					return false;
			}
			return true;
		}

		bool ViewFrustum::boxIntersectsWithFrustum(const AABB & box) const {
			const std::array<Vec3, 8>& vertices = box.getVertices();
			for (const Vec3& vertex : vertices) {
				if (pointInFrustum(vertex))
					return true;
			}
			return false;
		}
		
	}
}