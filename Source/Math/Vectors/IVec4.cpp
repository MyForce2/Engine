#pragma once

#include "IVec4.h"

#include "IVec2.h"
#include "IVec3.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

namespace Engine {
	namespace Math {


		IVec4::IVec4() : x(), y(), z(), w() {

		}

		IVec4::IVec4(int value) : x(value), y(value), z(value), w(value) {

		}

		IVec4::IVec4(int x, int y, int z, int w) : x(x), y(y), z(z), w(w) {

		}

		IVec4::IVec4(const IVec2& vec) : x(vec.x), y(vec.y), z(), w() {

		}

		IVec4::IVec4(const IVec2& vec, int z, int w) : x(vec.x), y(vec.y), z(z), w(w) {

		}

		IVec4::IVec4(const IVec3& vec) : x(vec.x), y(vec.y), z(vec.z) {

		}

		IVec4::IVec4(const IVec3& vec, int w) : x(vec.x), y(vec.y), z(vec.z), w() {

		}

		IVec4::IVec4(const IVec4& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {

		}

		IVec4::IVec4(const Vec2& vec) : x(vec.x), y(vec.y), z(), w() {

		}

		IVec4::IVec4(const Vec2& vec, int z, int w) : x(vec.x), y(vec.y), z(), w() {

		}

		IVec4::IVec4(const Vec3& vec) : x(vec.x), y(vec.y), z(vec.z) {

		}

		IVec4::IVec4(const Vec3& vec, int w) : x(vec.x), y(vec.y), z(vec.z), w(w) {

		}

		IVec4::IVec4(const Vec4& vec) : x(vec.x), y(vec.y), z(vec.z), w(vec.w) {

		}

		IVec4::~IVec4() {

		}

	}
}