#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>


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

		Mat4 Mat4::operator*(float value) const {
			Mat4 result((*this));
			for (int i = 0; i < 16; i++)
				result.data[i] *= value;
			return result;
		}

		Mat4 Mat4::operator/(float value) const {
			Mat4 result((*this));
			for (int i = 0; i < 16; i++)
				result.data[i] /= value;
			return result;
		}

		Mat4 Mat4::operator+(float value) const {
			Mat4 result((*this));
			for (int i = 0; i < 16; i++)
				result.data[i] += value;
			return result;
		}

		Mat4 Mat4::operator-(float value) const {
			Mat4 result((*this));
			for (int i = 0; i < 16; i++)
				result.data[i] -= value;
			return result;
		}

		Vec4 Mat4::operator*(const Vec4& vec) const {
			Vec4 result;
			float* vecData = (float*) (&vec);
			float* resultData = (float*) (&result);
			for (int i = 0; i < 4; i++) {
				float sum = 0.f;
				for (int j = 0; j < 4; j++) {
					sum += data[j * 4 + i] * vecData[j];
				}
				resultData[i] = sum;
			}
			return result;
		}

		void Mat4::operator*=(const Mat4& mat) {
			Mat4 result = (*this) * mat;
			for (int i = 0; i < 16; i++)
				data[i] = result.data[i];
		}

		void Mat4::operator*=(float value) {
			for (int i = 0; i < 16; i++)
				data[i] *= value;
		}

		void Mat4::operator/=(float value) {
			for (int i = 0; i < 16; i++)
				data[i] /= value;
		}

		void Mat4::operator+=(float value) {
			for (int i = 0; i < 16; i++)
				data[i] += value;
		}

		void Mat4::operator-=(float value) {
			for (int i = 0; i < 16; i++)
				data[i] -= value;
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

		Mat4 Mat4::rotationX(float angle) {
			Mat4 result(1.f);
			float rad = toRadians(angle);
			float c = std::cos(rad);
			float s = std::sin(rad);
			result[1].y = c;
			result[1].z = s;
			result[2].y = -s;
			result[2].z = c;
			return result;
		}

		Mat4 Mat4::rotationY(float angle) {
			Mat4 result(1.f);
			float rad = toRadians(angle);
			float c = std::cos(rad);
			float s = std::sin(rad);
			result[0].x = c;
			result[0].z = -s;
			result[2].x = s;
			result[2].z = c;
			return result;
		}

		Mat4 Mat4::rotationZ(float angle) {
			Mat4 result(1.f);
			float rad = toRadians(angle);
			float c = std::cos(rad);
			float s = std::sin(rad);
			result[0].x = c;
			result[0].y = s;
			result[1].x = -s;
			result[1].y = c;
			return result;
		}

		Mat4 Mat4::orthographic(float left, float right, float bottom, float top) {
			return orthographic(left, right, bottom, top, -1.f, 1.f);
		}

		Mat4 Mat4::orthographic(float left, float right, float bottom, float top, float near, float far) {
			Mat4 result(1.f);
			result[0].x = 2 / (right - left);
			result[1].y = 2 / (top - bottom);
			result[2].z = -2 / (far - near);
			result[3].x = (right + left) / (right - left) * -1;
			result[3].y = (top + bottom) / (top - bottom) * -1;
			result[3].z = (far + near) / (far - near) * -1;
			return result;
		}

		Mat4 Mat4::perspective(float aspectRatio, float fieldOfView, float near, float far) {
			Mat4 result;
			float radians = toRadians(fieldOfView);
			float t = std::tan(radians / 2);
			result[0].x = 1 / (aspectRatio * t);
			result[1].y = 1 / t;
			result[2].z = -(far + near) / (far - near);
			result[2].w = -1;
			result[3].z = -(2 * far * near) / (far - near);
			return result;
		}

		

		float toRadians(float angle) {
			return angle * M_PI / 180.f;
		}

		Mat4 operator*(float value, const Mat4& mat) {
			return mat * value;
		}

		Mat4 operator-(const Mat4& mat) {
			Mat4 result;
			for (int i = 0; i < 16; i++)
				result.data[i] = -mat.data[i];
			return result;
		}

		std::ostream& operator<<(std::ostream& os, const Mat4& mat) {
			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 4; j++) {
					os << mat.data[j * 4 + i] << ' ';
				}
				os << '\n';
			}
			return os;
		}
	}
}
