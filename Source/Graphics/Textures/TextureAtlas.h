#pragma once

#include "Texture.h"

#include <array>

namespace Engine {
	namespace Graphics {


		class TextureAtlas {
		private:
			Texture atlas;
			unsigned int atlasSize;
			float textureSize;

		public:
			TextureAtlas(const std::string& path, unsigned int atlasSize, unsigned int textureSize);
			~TextureAtlas();

			inline const Texture& getTexture() const { return atlas; }
			
			std::array<float, 8> getUVCoordinates(unsigned int textureOffset) const;
		};
	}
}