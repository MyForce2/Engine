#pragma once


namespace Engine {
	namespace Math {

		// Forward declaration

		struct IVec3;
		struct IVec4;
		struct Vec2;
		struct Vec3;
		struct Vec4;
		
		/*
		A glsl style vector struct used to hold and wrap two integral values
		*/
		struct IVec2 {
			int x, y;

			// Constructors

			IVec2();
			IVec2(int value);
			IVec2(int x, int y);
			IVec2(const IVec2& vec);
			IVec2(const IVec3& vec);
			IVec2(const IVec4& vec);
			IVec2(const Vec2& vec);
			IVec2(const Vec3& vec);
			IVec2(const Vec4& vec);
			~IVec2();
		};
	}
}