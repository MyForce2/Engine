#pragma once

#include "IVec3.h"

#include "IVec2.h"
#include "IVec4.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

namespace Engine {
	namespace Math {

		IVec3::IVec3() : x(), y(), z() {

		}

		IVec3::IVec3(int value) : x(value), y(value), z(value) {

		}

		IVec3::IVec3(int x, int y, int z) : x(x), y(y), z(z) {

		}

		IVec3::IVec3(const IVec2& vec) : x(vec.x), y(vec.y), z() {

		}

		IVec3::IVec3(const IVec2& vec, int z) : x(vec.x), y(vec.y), z(z) {

		}

		IVec3::IVec3(const IVec3& vec) : x(vec.x), y(vec.y), z(vec.z) {

		}

		IVec3::IVec3(const IVec4& vec) : x(vec.x), y(vec.y), z(vec.z) {

		}

		IVec3::IVec3(const Vec2& vec) : x(vec.x), y(vec.y), z() {

		}

		IVec3::IVec3(const Vec2& vec, int z) : x(vec.x), y(vec.y), z(z) {

		}

		IVec3::IVec3(const Vec3& vec) : x(vec.x), y(vec.y), z(vec.z) {

		}

		IVec3::IVec3(const Vec4& vec) : x(vec.x), y(vec.y), z(vec.z) {

		}

		IVec3::~IVec3() {

		}
	}
}