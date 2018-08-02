
#include "Vec2.h"

#include "Vec3.h"
#include "Vec4.h"
#include "IVec2.h"
#include "IVec3.h"
#include "IVec4.h"

namespace Engine {
	namespace Math {

		Vec2::Vec2() : x(), y() {

		}

		Vec2::Vec2(float value) : x(value), y(value) {

		}

		Vec2::Vec2(float x, float y) : x(x), y(y) {

		}

		Vec2::Vec2(const Vec3& vec) : x(vec.x), y(vec.y) {

		}

		Vec2::Vec2(const Vec4& vec) : x(vec.x), y(vec.y) {

		}

		Vec2::Vec2(const Vec2& vec) : x(vec.x), y(vec.y) {

		}

		Vec2::Vec2(const IVec2& vec) : x(vec.x), y(vec.y) {

		}

		Vec2::Vec2(const IVec3& vec) : x(vec.x), y(vec.y) {

		}

		Vec2::Vec2(const IVec4& vec) : x(vec.x), y(vec.y) {

		}

		Vec2::~Vec2() {

		}

		float Vec2::length() const {
			float sum = std::pow(x, 2) + std::pow(y, 2);
			return std::sqrt(sum);
		}

		void Vec2::normalize() {
			float vecLength = length();
			x /= vecLength;
			y /= vecLength;
		}

		Vec2 Vec2::normalized() const {
			float vecLength = length();
			return Vec2(x / vecLength, y / vecLength);
		}

		float Vec2::dot(const Vec2& vec) const {
			Vec2 multiplied = (*this) * vec;
			return multiplied.x + multiplied.y;
		}

		float Vec2::distance(const Vec2& vec) const {
			return Vec2(x - vec.x, y - vec.y).length();
		}

		Vec2 Vec2::operator+(float value) const {
			return Vec2(x + value, y + value);
		}

		Vec2 Vec2::operator-(float value) const {
			return Vec2(x - value, y - value);
		}

		Vec2 Vec2::operator*(float value) const {
			return Vec2(x * value, y * value);
		}

		Vec2 Vec2::operator/(float value) const {
			return Vec2(x / value, y / value);
		}

		void Vec2::operator+=(float value) {
			x += value;
			y += value;
		}

		void Vec2::operator-=(float value) {
			x -= value;
			y -= value;
		}

		void Vec2::operator*=(float value) {
			x *= value;
			y *= value;
		}

		void Vec2::operator/=(float value) {
			x /= value;
			y /= value;
		}

		Vec2 Vec2::operator+(const Vec2& vec) const {
			return Vec2(x + vec.x, y + vec.y);
		}

		Vec2 Vec2::operator-(const Vec2& vec) const {
			return Vec2(x - vec.x, y - vec.y);
		}

		Vec2 Vec2::operator*(const Vec2& vec) const {
			return Vec2(x * vec.x, y * vec.y);
		}

		Vec2 Vec2::operator/(const Vec2& vec) const {
			return Vec2(x / vec.x, y / vec.y);
		}

		void Vec2::operator+=(const Vec2& vec) {
			x += vec.x;
			y += vec.y;
		}

		void Vec2::operator-=(const Vec2& vec) {
			x -= vec.x;
			y -= vec.y;
		}

		void Vec2::operator*=(const Vec2& vec) {
			x *= vec.x;
			y *= vec.y;
		}
		void Vec2::operator/=(const Vec2& vec) {
			x /= vec.x;
			y /= vec.y;
		}

		bool Vec2::operator==(const Vec2& vec) const {
			return x == vec.x && y == vec.y;
		}

		bool Vec2::operator!=(const Vec2& vec) const {
			return !((*this) == vec);
		}

		Vec2 operator*(float value, const Vec2& vec) {
			return vec * value;
		}

		Vec2 operator-(const Vec2& vec) {
			return vec * -1;
		}

		std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
			os << "(" << vec.x << ", " << vec.y << ")";
			return os;
		}
	}

}


