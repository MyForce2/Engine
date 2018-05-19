#pragma once


#include <string>

#include "Vec3.h"

namespace Engine {
	namespace Math {

		Vec3::Vec3() : x(), y(), z() {

		}
		
		Vec3::Vec3(float value) : x(value), y(value), z(value) {

		}

		Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {

		}

		Vec3::Vec3(const Vec3& vec) : x(vec.x), y(vec.y), z(vec.z) {
		
		}

		Vec3::~Vec3() {

		}

		Vec3 Vec3::operator+(float value) const {
			return Vec3(x + value, y + value, z + value);
		}

		Vec3 Vec3::operator-(float value) const {
			return Vec3(x - value, y - value, z - value);
		}

		Vec3 Vec3::operator*(float value) const {
			return Vec3(x * value, y * value, z * value);
		}

		Vec3 Vec3::operator/(float value) const {
			return Vec3(x / value, y / value, z / value);
		}

		void Vec3::operator+=(float value) {
			x += value;
			y += value;
			z += value;
		}

		void Vec3::operator-=(float value) {
			x -= value;
			y -= value;
			z -= value;
		}

		void Vec3::operator*=(float value) {
			x *= value;
			y *= value;
			z *= value;
		}

		void Vec3::operator/=(float value) {
			x /= value;
			y /= value;
			z /= value;
		}

		Vec3 Vec3::operator+(const Vec3& vec) const {
			return Vec3(x + vec.x, y + vec.y, z + vec.z);
		}

		Vec3 Vec3::operator-(const Vec3& vec) const {
			return Vec3(x - vec.x, y - vec.y, z - vec.z);
		}

		Vec3 Vec3::operator*(const Vec3& vec) const {
			return Vec3(x * vec.x, y * vec.y, z * vec.z);
		}

		Vec3 Vec3::operator/(const Vec3& vec) const {
			return Vec3(x / vec.x, y / vec.y, z / vec.z);
		}

		void Vec3::operator+=(const Vec3& vec)  {
			x += vec.x;
			y += vec.y;
			z += vec.z;
		}

		void Vec3::operator-=(const Vec3& vec) {
			x -= vec.x;
			y -= vec.y;
			z -= vec.z;
		}

		void Vec3::operator*=(const Vec3& vec) {
			x *= vec.x;
			y *= vec.y;
			z *= vec.z;
		}

		void Vec3::operator/=(const Vec3& vec) {
			x /= vec.x;
			y /= vec.y;
			z /= vec.z;
		}

		bool Vec3::operator==(const Vec3& vec) const {
			return x == vec.x && y == vec.y && z == vec.z;
		}

		bool Vec3::operator!=(const Vec3& vec) const {
			return !((*this) == vec);
		}

		std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
			os << "(" << std::to_string(vec.x) << ", " << std::to_string(vec.y) << ", ";
			os << std::to_string(vec.z) << ")";
			return os;
		}

	}
}