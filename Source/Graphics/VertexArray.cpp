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
			unsigned int off = 0U;
			for (int i = 0; i < elements.size(); i++) {
				glEnableVertexAttribArray(i + amountOfAttributes);
				const VBElement& element = elements[i];
				GLint elementSize = VBElement::getSizeOfElement(element.type);
				if (VBElement::isInteger(element.type))
					glVertexAttribIPointer(i + amountOfAttributes, element.amount, element.type, layout.getStride(), (const void*) off);
				else if (VBElement::isDouble(element.type))
					glVertexAttribLPointer(i + amountOfAttributes, element.amount, element.type, layout.getStride(), (const void*) off);
				else
					glVertexAttribPointer(i + amountOfAttributes, element.amount, element.type, GL_FALSE, layout.getStride(), (const void*) off);
				off += element.amount * elementSize;
			}
			amountOfAttributes += elements.size();
			unBind();
		}

		void VertexArray::addMatrixBuffer(const VertexBuffer& vbo) {
			bind();
			vbo.bind();
			unsigned int offset = 0U;
			for (int i = 0; i < 4; i++) {
				glEnableVertexAttribArray(i + amountOfAttributes);
				glVertexAttribPointer(i + amountOfAttributes, 4, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 16, (const void*) offset);
				offset += sizeof(GLfloat) * 4;
			}
			amountOfAttributes += 4;
		}

		void VertexArray::addInstancedBuffer(const VertexBuffer& vbo, const VBLayout& layout) {
			bind();
			vbo.bind();
			std::vector<VBElement> elements = layout.getElements();
			unsigned int off = 0U;
			for (int i = 0; i < elements.size(); i++) {
				glEnableVertexAttribArray(i + amountOfAttributes);
				const VBElement& element = elements[i];
				GLint elementSize = VBElement::getSizeOfElement(element.type);
				if (VBElement::isInteger(element.type))
					glVertexAttribIPointer(i + amountOfAttributes, element.amount, element.type, layout.getStride(), (const void*) off);
				else if (VBElement::isDouble(element.type))
					glVertexAttribLPointer(i + amountOfAttributes, element.amount, element.type, layout.getStride(), (const void*) off);
				else
					glVertexAttribPointer(i + amountOfAttributes, element.amount, element.type, GL_FALSE, layout.getStride(), (const void*) off);
				glVertexAttribDivisor(i + amountOfAttributes, 1);
				off += element.amount * elementSize;
			}
			amountOfAttributes += elements.size();
			unBind();
		}

		void VertexArray::addInstancedMatrixBuffer(const VertexBuffer& vbo) {
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