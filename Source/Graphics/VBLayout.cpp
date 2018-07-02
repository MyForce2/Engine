#pragma once

#include "VBLayout.h"

namespace Engine {
	namespace Graphics {

		VBLayout::VBLayout() : stride(0U), elements() {

		}

		VBLayout::VBLayout(size_t amount, GLenum type) : stride(amount * VBElement::getSizeOfElement(type)), elements() {
			VBElement element = { amount, type };
			elements.push_back(element);
		}

		VBLayout::~VBLayout() {

		}

		void VBLayout::addElement(size_t amount, GLenum type) {
			VBElement element = { amount, type };
			elements.push_back(element);
			stride += amount * VBElement::getSizeOfElement(element.type);
		}
	}
}