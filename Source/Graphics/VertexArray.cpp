#pragma once

#include "VertexArray.h"

namespace Engine {
	namespace Graphics {

		VertexArray::VertexArray() : amountOfAttributes(0U) {
			glGenVertexArrays(1, &id);
			bind();
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
			Utils::LinkedList<VBElement> elements = layout.getElements();
			int i = 0;
			unsigned int off = 0U;
			for (VBElement& element : elements) {
				glEnableVertexAttribArray(i + amountOfAttributes);
				GLint size = VBElement::getSizeOfElement(element.type);
				glVertexAttribPointer(i + amountOfAttributes, element.amount, element.type, GL_FALSE, layout.getStride(), (const void*) off);
				off += element.amount * size;
				i++;
			}
			amountOfAttributes += i;
		}
	}
}