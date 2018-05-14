#pragma once

#include "Vec3.h"
#include "Vec4.h"

namespace Engine {
	namespace Math {

		/*
		A struct used to represent any type of matrix which is a 4x4 matrix
		*/
		struct Mat4 {
		public:
			union {
				float data[16];
				Vec4 columns[4];
			};

			Mat4();
			Mat4(float mainDiagonal);
			Mat4(const Mat4& mat);
			~Mat4();

			Mat4 operator*(const Mat4& mat) const;
			void operator*=(const Mat4& mat);

			Vec4& operator[](size_t index);
			Vec4 operator[](size_t index) const;

			static Mat4 translation(const Vec3& translation);
			static Mat4 scale(const Vec3& scale);
			static Mat4 rotateX(float angle);
			static Mat4 rotateY(float angle);
			static Mat4 rotateZ(float angle);
			static Mat4 rotation(float angle, const Vec3& axes);

		private:
			friend std::ostream& operator<<(std::ostream& os, const Mat4& mat);
		};

		float toRadians(float angle);
	}
}