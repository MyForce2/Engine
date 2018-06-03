
#include "Ray.h"


namespace Engine {
	namespace Math {

		Ray::Ray(const Vec3& start, const Vec3& end) : start(start), end(end) {

		}

		Ray::~Ray() {

		}

		float Ray::rayLength() const {
			return start.distance(end);
		}

		bool Ray::intersectsWith(const Plane& plane) const {
			float d = plane.getD();
			Vec3 normal = plane.getNormal();
			Vec3 normalStart = normal * start;
			Vec3 r(end.x - start.x, end.y - start.y, end.z - start.z);
			float k = d - normalStart.x - normalStart.y - normalStart.z;
			float s = (normal.x * r.x + normal.y * r.y + normal.z * r.z);
			float t = k / s;
			if (t == INFINITY || t == -INFINITY || t == 0)
				return false;
			return true;
		}

		bool Ray::intersectsWith(const Plane& plane, float maxDistance) const {
			float d = plane.getD();
			Vec3 normal = plane.getNormal();
			Vec3 normalStart = normal * start;
			Vec3 r(end.x - start.x, end.y - start.y, end.z - start.z);
			float k = d - normalStart.x - normalStart.y - normalStart.z;
			float s = (normal.x * r.x + normal.y * r.y + normal.z * r.z);
			float t = k / s;
			if (t == INFINITY || t == -INFINITY || t == 0)
				return false;
			Vec3 point = start + r * t;
			return start.distance(point) < maxDistance;
		}
	}
}