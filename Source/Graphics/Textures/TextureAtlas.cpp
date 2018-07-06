
#include "TextureAtlas.h"

namespace Engine {
	namespace Graphics {

		TextureAtlas::TextureAtlas(const std::string& path, unsigned int atlasSize, unsigned int textureSize) : atlas(path), 
			atlasSize(atlasSize), textureSize(float(textureSize) / atlasSize) {

		}

		TextureAtlas::~TextureAtlas() {

		}

		UVCoords TextureAtlas::getUVCoordinates(unsigned int textureOffset) const {
			float xMin = textureSize * textureOffset;
			float xMax = xMin + textureSize;
			float yMax = 1.f - textureSize * (textureOffset / 16);
			float yMin = yMax - textureSize;
			UVCoords uv;
			uv.topRight = Math::Vec2(xMax, yMax);
			uv.bottomLeft = Math::Vec2(xMin, yMin);
			return uv;
		}
	}
}