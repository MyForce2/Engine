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

			bool operator==(const Mat4& mat) const;
			bool operator!=(const Mat4& mat) const;

			// Generates a translation matrix, according to the translation vector
			static Mat4 translation(const Vec3& translation);
			// Generates a scale matrix, according to the scale vector
			static Mat4 scale(const Vec3& scale);
			// Generates a rotation matrix around the X axis (angle in degrees)
			static Mat4 rotateX(float angle);
			// Generates a rotation matrix around the Y axis (angle in degrees)
			static Mat4 rotateY(float angle);
			// Generates a rotation matrix around the Z axis (angle in degrees)
			static Mat4 rotateZ(float angle);
			// Generates a rotation matrix, around the axes given in the axes vector
			// Each axes is added to the rotation if the corresponding axes variable 
			// is set to 1 (Order is Z * Y * X)
			static Mat4 rotation(float angle, const Vec3& axes);
			// Generates a rotation matrix, around the axes given in the axes vector
			// Each axes is added to the rotation if the corresponding axes variable 
			// is set to 1 (Order is Z * Y * X)
			static Mat4 rotation(const Vec3& angles, const Vec3& axes);

		private:
			friend std::ostream& operator<<(std::ostream& os, const Mat4& mat);
		};

		// Converts an angle in degrees to radians
		float toRadians(float angle);
	}
}