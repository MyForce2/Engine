#pragma once

#include "Texture.h"

#include "Utils\ImageUtils.h"

namespace Engine {
	namespace Graphics {

		Texture::Texture(const std::string& path) {
			stbi_set_flip_vertically_on_load(1);
			int height = 0, width = 0, bitsPerPixel = 0;
			unsigned char* buffer = nullptr;
			buffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4);
			TextureData data = { GLsizei(width), GLsizei(height), buffer };
			init(data, GL_LINEAR);
			if (buffer)
				stbi_image_free(buffer);
		}

		Texture::Texture(const char* path) {
			stbi_set_flip_vertically_on_load(1);
			int height = 0, width = 0, bitsPerPixel = 0;
			unsigned char* buffer = nullptr;
			buffer = stbi_load(path, &width, &height, &bitsPerPixel, 4);
			TextureData data = { GLsizei(width), GLsizei(height), buffer };
			init(data, GL_LINEAR);
			if (buffer) 
				stbi_image_free(buffer);
		}

		Texture::Texture(const char* path, GLint filterParam) {
			stbi_set_flip_vertically_on_load(1);
			int height = 0, width = 0, bitsPerPixel = 0;
			unsigned char* buffer = nullptr;
			buffer = stbi_load(path, &width, &height, &bitsPerPixel, 4);
			TextureData data = { GLsizei(width), GLsizei(height), buffer };
			init(data, filterParam);
			if (buffer)
				stbi_image_free(buffer);
		}

		Texture::Texture(const std::string& path, GLint filterParam) {
			stbi_set_flip_vertically_on_load(1);
			int height = 0, width = 0, bitsPerPixel = 0;
			unsigned char* buffer = nullptr;
			buffer = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4);
			TextureData data = { GLsizei(width), GLsizei(height), buffer };
			init(data, filterParam);
			if (buffer)
				stbi_image_free(buffer);
		}

		Texture::Texture(const unsigned char* buffer, GLsizei width, GLsizei height) {
			TextureData data = { width, height, buffer };
			init(data, GL_LINEAR);
		}

		Texture::Texture(const unsigned char* buffer, GLsizei width, GLsizei height, GLint filterParam) {
			TextureData data = { width, height, buffer };
			init(data, filterParam);
		}

		Texture::Texture(const unsigned char* buffer, GLsizei width, GLsizei height, GLint internalFormat, GLenum format, GLint filterParam) {
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterParam);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterParam);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, buffer);
			unBind();
		}

		Texture::~Texture() {
			glDeleteTextures(1, &id);
			unBind();
		}

		void Texture::setSlot(unsigned int slot) const {
			glActiveTexture(GL_TEXTURE0 + slot);
			glBindTexture(GL_TEXTURE_2D, id);
		}

		void Texture::unBind() const {
			glBindTexture(GL_TEXTURE_2D, 0);
		}

		void Texture::init(const TextureData& data, GLint filterParam) {
			glGenTextures(1, &id);
			glBindTexture(GL_TEXTURE_2D, id);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterParam);
			//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 1);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterParam);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data.width, data.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data.data);
			//glGenerateMipmap(GL_TEXTURE_2D);
			unBind();
		}
	}
}
