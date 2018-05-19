#pragma once

#include <iostream>

namespace Engine {
	namespace Math {

		/*
		A struct used to hold and wrap two values
		*/
		struct Vec2 {
		public:
			float x, y;

			Vec2();
			Vec2(float value);
			Vec2(float x, float y);
			Vec2(const Vec2& vec);
			~Vec2();

			Vec2 operator+(float value) const;
			Vec2 operator-(float value) const;
			Vec2 operator*(float value) const;
			Vec2 operator/(float value) const;

			void operator+=(float value);
			void operator-=(float value);
			void operator*=(float value);
			void operator/=(float value);

			Vec2 operator+(const Vec2& vec) const;
			Vec2 operator-(const Vec2& vec) const;
			Vec2 operator*(const Vec2& vec) const;
			Vec2 operator/(const Vec2& vec) const;

			void operator+=(const Vec2& vec);
			void operator-=(const Vec2& vec);
			void operator*=(const Vec2& vec);
			void operator/=(const Vec2& vec);

			bool operator==(const Vec2& vec) const;
			bool operator!=(const Vec2& vec) const;

		private:
			friend std::ostream& operator<<(std::ostream& os, const Vec2& vec);
		};


	}
}
