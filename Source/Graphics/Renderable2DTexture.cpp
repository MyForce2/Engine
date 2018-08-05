#pragma once

#include "Renderable2DTexture.h"

namespace Engine {
	namespace Graphics {

		Renderable2DTexture::Renderable2DTexture(const GLvoid* data, GLsizeiptr size, const std::string& texturePath) : texture(new Texture(texturePath)), Renderable2D() {
			vbo = new VertexBuffer(data, size);
			VBLayout layout;
			layout.addElement(2, GL_FLOAT);
			layout.addElement(2, GL_FLOAT);
			vao.addBuffer(*vbo, layout);
		}

		Renderable2DTexture::Renderable2DTexture(const GLvoid* data, GLsizeiptr size, const std::string& texturePath, const Math::Mat4& modelMatrix) 
			: texture(new Texture(texturePath)), Renderable2D() {
			vbo = new VertexBuffer(data, size);
			VBLayout layout;
			layout.addElement(2, GL_FLOAT);
			layout.addElement(2, GL_FLOAT);
			vao.addBuffer(*vbo, layout);
			this->modelMatrix = modelMatrix;
		}

		Renderable2DTexture::Renderable2DTexture(const GLvoid* data, GLsizeiptr size, const Texture* texture) : texture(texture), Renderable2D() {
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