#pragma once

#include "Plane.h"

namespace Engine {
	namespace Math {

		Plane::Plane(const Vec3& pointA, const Vec3& pointB, const Vec3& pointC) {
			Vec3 pointAB = pointA - pointB;
			Vec3 pointAC = pointA - pointC;
			normal = pointAB.cross(pointAC);
			Vec3 normalA = normal * pointA;
			d = normalA.x + normalA.y + normal.z;
		}

		Plane::Plane(const Vec3& normal, const Vec3& point) : normal(normal) {
			Vec3 normalPoint = normal * point;
			d = normalPoint.x + normalPoint.y + normalPoint.z;
		}

		Plane::~Plane() {

		}

		std::ostream& operator<<(std::ostream& os, const Plane& plane) {
			os << "(Normal : " << plane.normal << ", D : " << plane.d;
			return os;
		}
	}
}
