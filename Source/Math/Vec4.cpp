#pragma once

#include "Vec4.h"

#include "Vec2.h"
#include "Vec3.h"

namespace Engine {
	namespace Math {

		Vec4::Vec4() : x(), y(), z(), w() {

		}

		Vec4::Vec4(float value) : x(value), y(value), z(value), w(value) {

		}

		Vec4::Vec4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {

		}

		Vec4::Vec4(const Vec2& vec) : x(vec.x), y(vec.y), z(), w() {

		}

		Vec4::Vec4(const Vec3& vec) : x(vec.x), y(vec.y), z(vec.z), w() {

		}

		Vec4::Vec4(const Vec4& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {

		}

		Vec4::Vec4(const Vec2& vec, float z, float w) : x(vec.x), y(vec.y), z(z), w(w) {

		}

		Vec4::Vec4(const Vec3& vec, float w) : x(vec.x), y(vec.y), z(vec.z), w(w) {

		}

		Vec4::~Vec4() {

		}

		float Vec4::length() const {
			float sum = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2) + std::pow(w, 2);
			return std::sqrt(sum);
		}

		void Vec4::normalize() {
			float vecLength = length();
			x /= vecLength;
			y /= vecLength;
			z /= vecLength;
			w /= vecLength;
		}

		Vec4 Vec4::normalized() const {
			float vecLength = length();
			return Vec4(x / vecLength, y / vecLength, z / vecLength, w / vecLength);
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

		Vec4 operator*(float value, const Vec4& vec) {
			return vec * value;
		}

		Vec4 operator-(const Vec4& vec) {
			return vec * -1;
		}

		std::ostream& operator<<(std::ostream& os, const Vec4& vec) {
			os << "(" << vec.x << ", " << vec.y << ", ";
			os << vec.z << ", " << vec.w << ")";
			return os;
		}
	}
}
