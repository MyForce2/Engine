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

			// Operators

			Mat4 operator*(const Mat4& mat) const;
			Mat4 operator*(float value) const;
			Mat4 operator/(float value) const;
			Mat4 operator+(float value) const;
			Mat4 operator-(float value) const;
			Vec4 operator*(const Vec4& mat) const;

			void operator*=(const Mat4& mat);
			void operator*=(float value);
			void operator/=(float value);
			void operator+=(float value);
			void operator-=(float value);

			Vec4& operator[](size_t index);
			Vec4 operator[](size_t index) const;

			bool operator==(const Mat4& mat) const;
			bool operator!=(const Mat4& mat) const;


			// Generates a translation matrix, according to the translation vector
			static Mat4 translation(const Vec3& translation);
			// Generates a scale matrix, according to the scale vector
			static Mat4 scale(const Vec3& scale);
			// Generates a rotation matrix around the X axis (angle in degrees)
			static Mat4 rotationX(float angle);
			// Generates a rotation matrix around the Y axis (angle in degrees)
			static Mat4 rotationY(float angle);
			// Generates a rotation matrix around the Z axis (angle in degrees)
			static Mat4 rotationZ(float angle);
			// Generates an orthographic matrix, according to the given parameters
			static Mat4 orthographic(float left, float right, float bottom, float top, float near, float far);
			// Generates an orthograpic matrix, according to the given parameters
			static Mat4 orthographic(float left, float right, float bottom, float top);
			// Generates a perspective matrix, according to the given parameters
			static Mat4 perspective(float aspectRation, float fieldOfView, float near, float far);

		private:

			// More operators

			friend Mat4 operator*(float value, const Mat4& mat);
			friend Mat4 operator-(const Mat4& mat);

			friend std::ostream& operator<<(std::ostream& os, const Mat4& mat);
		};

		// Converts an angle in degrees to radians
		float toRadians(float angle);
	}
}