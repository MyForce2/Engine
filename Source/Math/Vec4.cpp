#pragma once

#include <string>

#include "Vec4.h"

namespace Engine {
	namespace Math {

		Vec4::Vec4() : x(), y(), z(), w() {

		}

		Vec4::Vec4(float value) : x(value), y(value), z(value), w(value) {

		}

		Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {

		}

		Vec4::Vec4(const Vec4& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {

		}

		Vec4::~Vec4() {

		}

		Vec4 Vec4::operator+(float value) const {
			return Vec4(x + value, y + value, z + value, w + value);
		}

		Vec4 Vec4::operator-(float value) const {
			return Vec4(x - value, y - value, z - value, w - value);
		}

		Vec4 Vec4::operator*(float value) const {
			return Vec4(x * value, y * value, z * value, w * value);
		}

		Vec4 Vec4::operator/(float value) const {
			return Vec4(x / value, y / value, z / value, w / value);
		}

		void Vec4::operator+=(float value) {
			x += value;
			y += value;
			z += value;
			w += value;
		}

		void Vec4::operator-=(float value) {
			x -= value;
			y -= value;
			z -= value;
			w -= value;
		}

		void Vec4::operator*=(float value) {
			x *= value;
			y *= value;
			z *= value;
			w *= value;
		}

		void Vec4::operator/=(float value) {
			x /= value;
			y /= value;
			z /= value;
			w /= value;
		}

		Vec4 Vec4::operator+(const Vec4& vec) const {
			return Vec4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);
		}

		Vec4 Vec4::operator-(const Vec4& vec) const {
			return Vec4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);
		}

		Vec4 Vec4::operator*(const Vec4& vec) const {
			return Vec4(x * vec.x, y * vec.y, z * vec.z, w * vec.w);
		}

		Vec4 Vec4::operator/(const Vec4& vec) const {
			return Vec4(x / vec.x, y / vec.y, z / vec.z, w / vec.w);
		}

		void Vec4::operator+=(const Vec4& vec) {
			x += vec.x;
			y += vec.y;
			z += vec.z;
			w += vec.w;
		}

		void Vec4::operator-=(const Vec4& vec) {
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
			w -= vec.w;
		}

		void Vec4::operator*=(const Vec4& vec) {
			x *= vec.x;
			y *= vec.y;
			z *= vec.z;
			w *= vec.w;
		}

		void Vec4::operator/=(const Vec4& vec) {
			x /= vec.x;
			y /= vec.y;
			z /= vec.z;
			w /= vec.w;
		}

		bool Vec4::operator==(const Vec4& vec) const {
			return x == vec.x && y == vec.y && z == vec.z && w == vec.w;
		}

		bool Vec4::operator!=(const Vec4& vec) const {
			return !((*this) == vec);
		}

		std::ostream& operator<<(std::ostream& os, const Vec4& vec) {
			os << "(" << std::to_string(vec.x) << ", " << std::to_string(vec.y) << ", ";
			os << std::to_string(vec.z) << ", " << std::to_string(vec.w) << ")";
			return os;
		}
	}
}
