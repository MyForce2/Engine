#pragma once

#include "Vectors/Vec3.h"

namespace Engine {
	namespace Math {
		
		/*
		A class that represents a plane
		*/
		class Plane {
		private:
			// The normal vector to this plane
			Vec3 normal;
			// The sum of th plane equation
			float d;

		public:
			Plane(const Vec3& pointA, const Vec3& pointB, const Vec3& pointC);
			Plane(const Vec3& normal, const Vec3& point);
			~Plane();

			inline const Vec3& getNormal() const { return normal; }
			inline float getD() const { return d; }
			// Returns the signed distance between a point and this plane
			float distance(const Vec3& point) const;
			// Returns whether the given point exists on this plane
			bool exists(const Vec3& point) const;

		private:
			friend std::ostream& operator<<(std::ostream& os, const Plane& plane);
		};
	}
}