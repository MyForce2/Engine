#pragma once

#include "Mat3.h"
#include "Mat4.h"

namespace Engine {
	namespace Math {

		Mat3::Mat3() {
			for (int i = 0; i < DATA_SIZE; i++)
				data[i] = 0.f;
		}

		Mat3::Mat3(float mainDiagonal) {
			for (int i = 0; i < DATA_SIZE; i++)
				data[i] = 0.f;
			data[0] = mainDiagonal;
			data[4] = mainDiagonal;
			data[8] = mainDiagonal;
		}

		Mat3::Mat3(const Mat3& mat) {
			for (int i = 0; i < DATA_SIZE; i++)
				data[i] = mat.data[i];
		}

		Mat3::Mat3(const Mat4& mat) {
			for (int i = 0; i < MATRIX_DIMENSIONS; i++)
				columns[i] = Vec3(mat.columns[i]);
		}

		Mat3::~Mat3() {

		}

		Mat3 Mat3::operator*(const Mat3& mat) const {
			Mat3 result;
			for (int i = 0; i < MATRIX_DIMENSIONS; i++) {
				for (int j = 0; j < MATRIX_DIMENSIONS; j++) {
					float sum = 0.f;
					for (int k = 0; k < MATRIX_DIMENSIONS; k++) {
						sum += data[j + k * MATRIX_DIMENSIONS] * mat.data[k + i * MATRIX_DIMENSIONS];
					}
					result.data[j + i * MATRIX_DIMENSIONS] = sum;
				}
			}
			return result;
		}

		Mat3 Mat3::operator*(float value) const {
			Mat3 result;
			for (int i = 0; i < DATA_SIZE; i++)
				result.data[i] = data[i] * value;
			return result;
		}

		Mat3 Mat3::operator/(float value) const {
			Mat3 result;
			for (int i = 0; i < DATA_SIZE; i++)
				result.data[i] = data[i] / value;
			return result;
		}

		Mat3 Mat3::operator+(float value) const {
			Mat3 result;
			for (int i = 0; i < DATA_SIZE; i++)
				result.data[i] = data[i] + value;
			return result;
		}

		Mat3 Mat3::operator-(float value) const {
			Mat3 result;
			for (int i = 0; i < DATA_SIZE; i++)
				result.data[i] = data[i] - value;
			return result;
		}

		Vec3 Mat3::operator*(const Vec3& vec) const {
			Vec3 result;
			float* vecData = (float*) (&vec);
			float* resultData = (float*) (&result);
			for (int i = 0; i < MATRIX_DIMENSIONS; i++) {
				float sum = 0.f;
				for (int j = 0; j < MATRIX_DIMENSIONS; j++) {
					sum += data[j * MATRIX_DIMENSIONS + i] * vecData[j];
				}
				resultData[i] = sum;
			}
			return result;
		}

		void Mat3::operator*=(const Mat3& mat) {
			Mat3 result = (*this) * mat;
			for (int i = 0; i < DATA_SIZE; i++)
				data[i] = result.data[i];
		}

		void Mat3::operator*=(float value) {
			for (int i = 0; i < DATA_SIZE; i++)
				data[i] *= value;
		}

		void Mat3::operator/=(float value) {
			for (int i = 0; i < DATA_SIZE; i++)
				data[i] /= value;
		}

		void Mat3::operator+=(float value) {
			for (int i = 0; i < DATA_SIZE; i++)
				data[i] += value;
		}

		void Mat3::operator-=(float value) {
			for (int i = 0; i < DATA_SIZE; i++)
				data[i] -= value;
		}

		Vec3& Mat3::operator[](size_t index) {
			return columns[index];
		}

		Vec3 Mat3::operator[](size_t index) const {
			return columns[index];
		}

		bool Mat3::operator==(const Mat3& mat) const {
			for (int i = 0; i < DATA_SIZE; i++) {
				if (data[i] != mat.data[i])
					return false;
			}
			return true;
		}

		bool Mat3::operator!=(const Mat3& mat) const {
			return !((*this) == mat);
		}

		Mat3 operator-(const Mat3& mat) {
			Mat3 result;
			for (int i = 0; i < Mat3::DATA_SIZE; i++)
				result[i] = -mat.data[i];
			return result;
		}
	}
}
