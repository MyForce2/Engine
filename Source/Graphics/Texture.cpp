#pragma once

#include "Texture.h"

#include "Utils\ImageUtils.h"

namespace Engine {
	namespace Graphics {

		Texture::Texture(const std::string& path) {
			stbi_set_flip_vertically_on_load(1);
			int height, width, bitsPerPixel;
			unsigned char* buffer = nullptr;
			buffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4);
			
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
			unBind();
			if (buffer) 
				stbi_image_free(buffer);
		}

		Texture::Texture(const char* path) {
			stbi_set_flip_vertically_on_load(1);
			int height = 0, width = 0, bitsPerPixel = 0;
			unsigned char* buffer = nullptr;
			buffer = stbi_load(path, &width, &height, &bitsPerPixel, 4);

			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);
			unBind();
			if (buffer) 
				stbi_image_free(buffer);
		}

		Texture::~Texture() {
			glDeleteTextures(1, &id);
		}

		void Texture::setSlot(unsigned int slot) const {
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, id);
		}

		void Texture::unBind() const {
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}
