#pragma once

#include "VertexArray.h"

namespace Engine {
	namespace Graphics {

		VertexArray::VertexArray() : amountOfAttributes(0U) {
			glGenVertexArrays(1, &id);
		}

		VertexArray::~VertexArray() {
			glDeleteVertexArrays(1, &id);
			unBind();
		}

		void VertexArray::bind() const {
			glBindVertexArray(id);
		}

		void VertexArray::unBind() const {
			glBindVertexArray(0);
		}

		void VertexArray::addBuffer(const VertexBuffer& vbo, const VBLayout& layout) {
			bind();
			vbo.bind();
			std::vector<VBElement> elements = layout.getElements();
			size_t size = elements.size();
			unsigned int off = 0U;
			for (int i = 0; i < size; i++) {
				glEnableVertexAttribArray(i + amountOfAttributes);
				const VBElement& element = elements[i];
				GLint elementSize = VBElement::getSizeOfElement(element.type);
				glVertexAttribPointer(i + amountOfAttributes, element.amount, element.type, GL_FALSE, layout.getStride(), (const void*) off);
				off += element.amount * elementSize;
			}
			amountOfAttributes += size;
			unBind();
		}

		void VertexArray::addMatrixBuffer(const VertexBuffer& vbo) {
			bind();
			vbo.bind();
			unsigned int offset = 0U;
			for (int i = 0; i < 4; i++) {
				glEnableVertexAttribArray(i + amountOfAttributes);
				glVertexAttribPointer(i + amountOfAttributes, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 16, (const void*) offset);
				glVertexAttribDivisor(i + amountOfAttributes, 1);
				offset += sizeof(GLfloat) * 4;
			}
			amountOfAttributes += 4;
		}
	}
}