#pragma once

#include <iostream>

namespace Engine {
	namespace Math {

		/*
		A struct used to hold and wrap four values
		*/
		struct Vec4 {
			float x, y, z, w;

			Vec4();
			Vec4(float value);
			Vec4(float x, float y, float z, float w);
			Vec4(const Vec4& vec);
			~Vec4();

			float length() const;
			void normalize();
			Vec4 normalized() const;

			Vec4 operator+(float value) const;
			Vec4 operator-(float value) const;
			Vec4 operator*(float value) const;
			Vec4 operator/(float value) const;

			void operator+=(float value);
			void operator-=(float value);
			void operator*=(float value);
			void operator/=(float value);

			Vec4 operator+(const Vec4& vec) const;
			Vec4 operator-(const Vec4& vec) const;
			Vec4 operator*(const Vec4& vec) const;
			Vec4 operator/(const Vec4& vec) const;

			void operator+=(const Vec4& vec);
			void operator-=(const Vec4& vec);
			void operator*=(const Vec4& vec);
			void operator/=(const Vec4& vec);

			bool operator==(const Vec4& vec) const;
			bool operator!=(const Vec4& vec) const;

		private:
			friend std::ostream& operator<<(std::ostream& os, const Vec4& vec);
		};
	}
}