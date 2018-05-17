#pragma once

#include "VBLayout.h"

namespace Engine {
	namespace Graphics {

		VBLayout::VBLayout() : stride(0U), elements() {

		}

		VBLayout::~VBLayout() {

		}

		void VBLayout::addElement(size_t amount, GLenum type) {
			VBElement element = { amount, type };
			elements.addLast(element);
			stride += amount * VBElement::getSizeOfElement(element.type);
		}
	}
}