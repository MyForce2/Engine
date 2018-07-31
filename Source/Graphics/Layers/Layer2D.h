#pragma once

#include "Math/Mat4.h"
#include "Graphics/Shader.h"
#include "Graphics/Rendering/BatchRenderer.h"

namespace Engine {
	namespace Graphics {

		class Layer2D {
		private:
			Math::Mat4 projection;
			Math::Mat4 view;
			BatchRenderer renderer;
			Shader shader;

			static const float PROJECTION_TOP;
			static const float PROJECTION_LEFT;
			
		public:
			Layer2D(float top, float right, const std::string& vertex, const std::string& fragment, const Font& font);
			Layer2D(const std::string& vertex, const std::string& fragment, const Font& font);
			Layer2D(const Math::Mat4& projection, const std::string& vertex, const std::string& fragment, const Font& font);

			void add(const Label& label);
			void add(const Renderable2DTexture& renderable);

			void setProjection(const Math::Mat4& projection);
			void setView(const Math::Mat4& view);

			void startFrame();
			void render();

		private:
			void initShader();
		};
	}
}