#pragma once

#include <iostream>

namespace Engine {
	namespace Math {

		struct Vec4;
		struct Vec2;

		/*
		A struct used to hold and wrap three values
		*/
		struct Vec3 {
		public:
			float x, y, z;

			Vec3();
			Vec3(float value);
			Vec3(float x, float y, float z);
			Vec3(const Vec2& vec);
			Vec3(const Vec4& vec);
			Vec3(const Vec3& vec);
			~Vec3();

			// Returns the length of this vector
			float length() const;
			// Normalizes this vector
			void normalize();
			// Returns a normalized version of this vector
			Vec3 normalized() const;
			// Returns the cross product of this vector and the given vector
			Vec3 cross(const Vec3& vec) const;
			// Returns the dot product of this vector and the given vector
			float dot(const Vec3& vec) const;
			// Returns the distance between this vector and the given vector
			float distance(const Vec3& vec) const;

			// Operators
			
			Vec3 operator+(float value) const;
			Vec3 operator-(float value) const;
			Vec3 operator*(float value) const;
			Vec3 operator/(float value) const;

			void operator+=(float value);
			void operator-=(float value);
			void operator*=(float value);
			void operator/=(float value);

			Vec3 operator+(const Vec3& vec) const;
			Vec3 operator-(const Vec3& vec) const;
			Vec3 operator*(const Vec3& vec) const;
			Vec3 operator/(const Vec3& vec) const;

			void operator+=(const Vec3& vec);
			void operator-=(const Vec3& vec);
			void operator*=(const Vec3& vec);
			void operator/=(const Vec3& vec);

			bool operator==(const Vec3& vec) const;
			bool operator!=(const Vec3& vec) const;

		private:

			// More operators

			friend Vec3 operator*(float value, const Vec3& vec);
			friend Vec3 operator-(const Vec3& vec);

			friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);
		};
	}
}