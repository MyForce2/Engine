#pragma once

#include <vector>

#include "VBElement.h"
#include "Utils\LinkedList.h"
#include "VertexBuffer.h"

namespace Engine {
	namespace Graphics {

		/*
		A class describing the layout a vertex buffer
		*/
		class VBLayout {
		private:
			// A list of all of the elements 
			Utils::LinkedList<VBElement> elements;
			// The amount of bytes per generic components in this layout
			GLsizei stride;

		public:
			VBLayout();
			~VBLayout();

			// Adds an element to this layout
			void addElement(size_t amount, GLenum type);

			inline const Utils::LinkedList<VBElement>& getElements() const { return elements; };
			inline GLsizei getStride() const { return stride; };

		};


	}
}
