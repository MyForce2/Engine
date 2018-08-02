#pragma once

namespace Engine {
	namespace Math {

		// Forward declaration

		struct IVec2;
		struct IVec4;
		struct Vec2;
		struct Vec3;
		struct Vec4;

		/*
		A glsl style vector struct used to hold and wrap three integral values
		*/
		struct IVec3 {
			int x, y, z;

			// Constructors

			IVec3();
			IVec3(int value);
			IVec3(int x, int y, int z);
			IVec3(const IVec2& vec);
			IVec3(const IVec2& vec, int z);
			IVec3(const IVec3& vec);
			IVec3(const IVec4& vec);
			IVec3(const Vec2& vec);
			IVec3(const Vec2& vec, int z);
			IVec3(const Vec3& vec);
			IVec3(const Vec4& vec);
			~IVec3();
		};
		
	}
}
