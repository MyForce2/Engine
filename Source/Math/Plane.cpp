#pragma once

#include "Plane.h"

namespace Engine {
	namespace Math {

		Plane::Plane(const Vec3& pointA, const Vec3& pointB, const Vec3& pointC) {
			Vec3 AC = pointC - pointA;
			Vec3 AB = pointB - pointA;
			normal = AC.cross(AB);
			Vec3 normalPoint = normal * pointA;
			d = -(normalPoint.x + normalPoint.y + normalPoint.z);
		}

		Plane::Plane(const Vec3& normal, const Vec3& point) : normal(normal) {
			Vec3 normalPoint = normal * point;
			d = -(normalPoint.x + normalPoint.y + normalPoint.z);
		}

		Plane::~Plane() {

		}

		float Plane::distance(const Vec3& point) const {
			float len = normal.length();
			Vec3 normalP = normal * point;
			return (normalP.x + normalP.y + normalP.z + d) / len;
		}

		bool Plane::exists(const Vec3& point) const {
			return point * normal == -d;
		}


		std::ostream& operator<<(std::ostream& os, const Plane& plane) {
			os << "(Normal : " << plane.normal << ", D : " << plane.d;
			return os;
		}
	}
}
