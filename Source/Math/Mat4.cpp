#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <string>


#include "Mat4.h"
#include "Vec2.h"

namespace Engine {
	namespace Math {

		Mat4::Mat4() {
			for (int i = 0; i < 16; i++)
				data[i] = 0.f;
		}

		Mat4::Mat4(float mainDiagonal) {
			for (int i = 0; i < 16; i++) 
				data[i] = 0.f;
			for (int i = 0; i < 16; i += 5)
				data[i] = mainDiagonal;
		}

		Mat4::Mat4(const Mat4& mat) {
			for (int i = 0; i < 16; i++)
				data[i] = mat.data[i];
		}

		Mat4::~Mat4() {

		}

		Mat4 Mat4::operator*(const Mat4& mat) const {
			Mat4 result;
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					float sum = 0.f;
					for (int k = 0; k < 4; k++) {
						sum += data[j + k * 4] * mat.data[k + i * 4];
					}
					result.data[j + i * 4] = sum;
				}
			}
			return result;
		}


		void Mat4::operator*=(const Mat4& mat) {
			Mat4 result = (*this) * mat;
			for (int i = 0; i < 16; i++)
				data[i] = result.data[i];
		}

		Vec4 Mat4::operator[](size_t index) const {
			return columns[index];
		}

		Vec4& Mat4::operator[](size_t index) {
			return columns[index];
		}

		bool Mat4::operator==(const Mat4& mat) const {
			for (int i = 0; i < 16; i++) {
				if (data[i] != mat.data[i])
					return false;
			}
			return true;
		}

		bool Mat4::operator!=(const Mat4& mat) const {
			return !((*this) == mat);
		}

		Mat4 Mat4::translation(const Vec3& translation) {
			Mat4 result(1.f);
			result[3].x = translation.x;
			result[3].y = translation.y;
			result[3].z = translation.z;
			return result;
		}

		Mat4 Mat4::scale(const Vec3& scale) {
			Mat4 result(1.f);
			result[0].x = scale.x;
			result[1].y = scale.y;
			result[2].z = scale.z;
			return result;
		}

		Mat4 Mat4::rotateX(float angle) {
			Mat4 result(1.f);
			float rad = toRadians(angle);
			float c = cos(rad);
			float s = sin(rad);
			result[1].y = c;
			result[1].z = s;
			result[2].y = -s;
			result[2].z = c;
			return result;
		}

		Mat4 Mat4::rotateY(float angle) {
			Mat4 result(1.f);
			float rad = toRadians(angle);
			float c = cos(rad);
			float s = sin(rad);
			result[0].x = c;
			result[0].z = -s;
			result[2].x = s;
			result[2].z = c;
			return result;
		}

		Mat4 Mat4::rotateZ(float angle) {
			Mat4 result(1.f);
			float rad = toRadians(angle);
			float c = cos(rad);
			float s = sin(rad);
			result[0].x = c;
			result[0].y = s;
			result[1].x = -s;
			result[1].y = c;
			return result;
		}


		Mat4 Mat4::rotation(float angle, const Vec3& axes) {
			Mat4 result(1.f);
			float rad = toRadians(angle);
			float c = cos(rad);
			float s = sin(rad);
			Vec2 x(axes.x * c, axes.x * s);
			Vec2 y(axes.y * c, axes.y * s);
			Vec2 z(axes.z * c, axes.z * s);
			result[0].x = y.x * z.x;
			result[0].y = y.x * z.y;
			result[0].z = -y.x;
			result[1].x = (z.x * x.y * y.y) - (y.x * z.y);
			result[1].y = (x.x * z.x) + (x.y * y.y * z.y);
			result[1].z = y.x * x.y;
			result[2].x = (x.x * z.x * y.y) + (x.y * z.y);
			result[2].y = (x.x * y.y * z.y) - (z.x * x.y);
			result[2].z = x.x * y.x;
			return result;
		}

		Mat4 Mat4::rotation(const Vec3& angles, const Vec3& axes) {
			Mat4 result(1.f);
			float radX = toRadians(angles.x);
			float radY = toRadians(angles.y);
			float radZ = toRadians(angles.z);
			Vec2 x(axes.x * cos(radX), axes.x * sin(radX));
			Vec2 y(axes.y * cos(radY), axes.y * sin(radY));
			Vec2 z(axes.z * cos(radZ), axes.z * sin(radZ));
			result[0].x = y.x * z.x;
			result[0].y = y.x * z.y;
			result[0].z = -y.x;
			result[1].x = (z.x * x.y * y.y) - (y.x * z.y);
			result[1].y = (x.x * z.x) + (x.y * y.y * z.y);
			result[1].z = y.x * x.y;
			result[2].x = (x.x * z.x * y.y) + (x.y * z.y);
			result[2].y = (x.x * y.y * z.y) - (z.x * x.y);
			result[2].z = x.x * y.x;
			return result;
		}

		

		float toRadians(float angle) {
			return angle * M_PI / 180.f;
		}

		std::ostream& operator<<(std::ostream& os, const Mat4& mat) {
			for (int i = 0; i < 16; i++) {
				if (i % 4 == 0 && i != 0)
					os << '\n';
				os << mat.data[i] << ' ';
			}
			return os;
		}
	}
}
