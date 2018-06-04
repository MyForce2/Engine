#pragma once

#include "BasicRenderer.h"


namespace Engine {
	namespace Graphics {

		BasicRenderer::BasicRenderer() {}
		BasicRenderer::~BasicRenderer() {} 
		
		void BasicRenderer::renderArraysInstanced(const VertexArray& vao, const Shader& shader, GLint first, GLsizei count, GLsizei instances) const {
			vao.bind();
			shader.bind();
			glDrawArraysInstanced(GL_TRIANGLES, first, count, instances);
			vao.unBind();
			shader.unBind();
		}

		void BasicRenderer::renderArrays(const VertexArray& vao, const Shader& shader, GLint first, GLsizei count) const {
			vao.bind();
			shader.bind();
			glDrawArrays(GL_TRIANGLES, first, count);
			vao.unBind();
			shader.unBind();
		}

		void BasicRenderer::renderElementsInstanced(const VertexArray& vao, const Shader& shader, const IndexBuffer& ibo, GLsizei instances) const {
			vao.bind();
			shader.bind();
			ibo.bind();
			glDrawElementsInstanced(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_BYTE, nullptr, instances);
			vao.unBind();
			shader.unBind();
			ibo.unBind();
		}

		void BasicRenderer::renderElements(const VertexArray& vao, const Shader& shader, const IndexBuffer& ibo) const {
			vao.bind();
			shader.bind();
			ibo.bind();
			glDrawElements(GL_TRIANGLES, ibo.getCount(), GL_UNSIGNED_BYTE, nullptr);
			vao.unBind();
			shader.unBind();
			ibo.unBind();
		}
	}
}