
#include "IVec2.h"

#include "IVec3.h"
#include "IVec4.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

namespace Engine {
	namespace Math {

		IVec2::IVec2() : x(), y() {

		}

		IVec2::IVec2(int value) : x(value), y(value) {

		}

		IVec2::IVec2(int x, int y) : x(x), y(y) {

		}

		IVec2::IVec2(const IVec2& vec) : x(vec.x), y(vec.y) {

		}

		IVec2::IVec2(const IVec3& vec) : x(vec.x), y(vec.y) {

		}

		IVec2::IVec2(const IVec4& vec) : x(vec.x), y(vec.y) {

		}

		IVec2::IVec2(const Vec2& vec) : x(int(vec.x)), y(int(vec.y)) {

		}

		IVec2::IVec2(const Vec3& vec) : x(int(vec.x)), y(int(vec.y)) {

		}

		IVec2::IVec2(const Vec4& vec) : x(int(vec.x)), y(int(vec.y)) {

		}

		IVec2::~IVec2() {

		}
	}
}