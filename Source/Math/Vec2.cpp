#pragma once

#include <string>

#include "Vec2.h"

namespace Engine {
	namespace Math {

		Vec2::Vec2() : x(), y() {

		}

		Vec2::Vec2(float value) : x(value), y(value) {

		}

		Vec2::Vec2(float x, float y) : x(x), y(y) {

		}

		Vec2::Vec2(const Vec2& vec) : x(vec.x), y(vec.y) {

		}

		Vec2::~Vec2() {

		}

		Vec2 Vec2::operator+(const Vec2& vec) const {
			Vec2 result;
			result.x = x + vec.x;
			result.y = y + vec.y;
			return result;
		}

		Vec2 Vec2::operator-(const Vec2& vec) const {
			Vec2 result;
			result.x = x - vec.x;
			result.y = y - vec.y;
			return result;
		}

		Vec2 Vec2::operator*(const Vec2& vec) const {
			Vec2 result;
			result.x = x * vec.x;
			result.y = y * vec.y;
			return result;
		}

		Vec2 Vec2::operator/(const Vec2& vec) const {
			Vec2 result;
			result.x = x / vec.x;
			result.y = y / vec.y;
			return result;
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

		std::ostream& operator<<(std::ostream& os, const Vec2& vec) {
			os << "(" << std::to_string(vec.x) << ", " << std::to_string(vec.y) << ")";
			return os;
		}
	}

}


