#pragma once

#include <iostream>

namespace Engine {
	namespace Math {

		/*
		A struct used to hold and wrap three values
		*/
		struct Vec3 {
		public:
			float x, y, z;

			Vec3();
			Vec3(float value);
			Vec3(float x, float y, float z);
			Vec3(const Vec3& vec);
			~Vec3();
			

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
			friend std::ostream& operator<<(std::ostream& os, const Vec3& vec);
		};
	}
}