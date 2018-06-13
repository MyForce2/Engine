
#include "TextureAtlas.h"

namespace Engine {
	namespace Graphics {

		TextureAtlas::TextureAtlas(const std::string& path, unsigned int atlasSize, unsigned int textureSize) : atlas(path), 
			atlasSize(atlasSize), textureSize(float(textureSize) / atlasSize) {

		}

		TextureAtlas::~TextureAtlas() {

		}

		std::array<float, 8> TextureAtlas::getUVCoordinates(unsigned int textureOffset) const {
			float xMin = textureSize * textureOffset;
			float xMax = xMin + textureSize;
			float yMax = 1.f - textureSize * (textureOffset / 16);
			float yMin = yMax - textureSize;
			std::array<float, 8> UVCoords =
			{
				xMax, yMax,
				xMin, yMax,
				xMin, yMin,
				xMax, yMin
			};
			return UVCoords;
		}
	}
}