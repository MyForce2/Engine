#pragma once

#include "Renderable2DTexture.h"

namespace Engine {
	namespace Graphics {

		Renderable2DTexture::Renderable2DTexture(const GLvoid* data, GLsizeiptr size, const std::string& texturePath) : texture(texturePath) {
			vbo = new VertexBuffer(data, size);
			VBLayout layout;
			layout.addElement(2, GL_FLOAT);
			layout.addElement(2, GL_FLOAT);
			vao.addBuffer(*vbo, layout);
		}

		Renderable2DTexture::~Renderable2DTexture() {

		}
	}
}