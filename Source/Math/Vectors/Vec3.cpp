


#include "Vec3.h"

#include "Vec2.h"
#include "Vec4.h"
#include "IVec2.h"
#include "IVec3.h"
#include "IVec4.h"

namespace Engine {
	namespace Math {

		Vec3::Vec3() : x(), y(), z() {

		}
		
		Vec3::Vec3(float value) : x(value), y(value), z(value) {

		}

		Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {

		}

		Vec3::Vec3(const Vec2& vec) : x(vec.x), y(vec.y), z() {

		}

		Vec3::Vec3(const Vec4& vec) : x(vec.x), y(vec.y), z(vec.z) {

		}

		Vec3::Vec3(const Vec3& vec) : x(vec.x), y(vec.y), z(vec.z) {
		
		}
		
		Vec3::Vec3(const Vec2& vec, float z) : x(vec.x), y(vec.y), z(z) {

		}

		Vec3::Vec3(const IVec2& vec) : x(vec.x), y(vec.y), z() {

		}

		Vec3::Vec3(const IVec2& vec, float z) : x(vec.x), y(vec.y), z(z) {

		}

		Vec3::Vec3(const IVec3& vec) : x(vec.x), y(vec.y), z(vec.z) {

		}

		Vec3::Vec3(const IVec4& vec) : x(vec.x), y(vec.y), z(vec.z) {

		}

		Vec3::~Vec3() {

		}
		
		float Vec3::length() const {
			float sum = std::pow(x, 2) + std::pow(y, 2) + std::pow(z, 2);
			return std::sqrt(sum);
		}

		void Vec3::normalize() {
			float vecLength = length();
			x /= vecLength;
			y /= vecLength;
			z /= vecLength;
		}

		Vec3 Vec3::normalized() const {
			float vecLength = length();
			return Vec3(x / vecLength, y / vecLength, z / vecLength);
		}

		Vec3 Vec3::cross(const Vec3& vec) const {
			Vec3 result;
			result.x = y * vec.z - z * vec.y;
			result.y = z * vec.x - x * vec.z;
			result.z = x * vec.y - y * vec.x;
			return result;
		}

		float Vec3::dot(const Vec3& vec) const {
			Vec3 multiplied = (*this) * vec;
			return multiplied.x + multiplied.y + multiplied.z;
		}

		float Vec3::distance(const Vec3& vec) const {
			return Vec3(x - vec.x, y - vec.y, z - vec.z).length();
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

		Vec3 operator*(float value, const Vec3& vec) {
			return vec * value;
		}

		Vec3 operator-(const Vec3& vec) {
			return vec * -1;
		}

		std::ostream& operator<<(std::ostream& os, const Vec3& vec) {
			os << "(" << vec.x << ", " << vec.y << ", ";
			os << vec.z << ")";
			return os;
		}

	}
}