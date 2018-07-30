#pragma once

#include "FrameBuffer.h"

#include "Utils/Log.h"


namespace Engine {
	namespace Graphics {


		FrameBuffer::FrameBuffer(float width, float height) : windowSize(width, height) {
			handleCreation();
			if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
				Utils::Log::getLog()->logError("Failed to create frame buffer, id : [" + bufferID + ']');
		}

		FrameBuffer::~FrameBuffer() {
			glDeleteTextures(1, &textureID);
			glDeleteFramebuffers(1, &bufferID);
			glDeleteRenderbuffers(1, &rboID);
		}

		void FrameBuffer::bind() const {
			glBindFramebuffer(GL_FRAMEBUFFER, bufferID);
		}

		void FrameBuffer::unBind() const {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		void FrameBuffer::bindTexture() const {
			glBindTexture(GL_TEXTURE_2D, textureID);
		}

		void FrameBuffer::unBindTexture() const {
			glBindTexture(GL_TEXTURE_2D, textureID);
		}

		void FrameBuffer::bindRenderBuffer() const {
			glBindRenderbuffer(GL_RENDERBUFFER, rboID);
		}

		void FrameBuffer::unBindRenderBuffer() const {
			glBindRenderbuffer(GL_RENDERBUFFER, 0);
		}

		void FrameBuffer::clearBuffer(GLbitfield mask) {
			glClear(mask);
		}

		void FrameBuffer::setSize(const Math::Vec2& size) {
			windowSize = size;
			glDeleteTextures(1, &textureID);
			glDeleteRenderbuffers(1, &rboID);
			glDeleteFramebuffers(1, &bufferID);
			handleCreation();
		}

		void FrameBuffer::handleCreation() {
			glGenTextures(1, &textureID);
			glGenRenderbuffers(1, &rboID);
			glGenFramebuffers(1, &bufferID);
			bind();
			bindTexture();
			bindRenderBuffer();
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, GLsizei(windowSize.x), GLsizei(windowSize.y), 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, GLsizei(windowSize.x), GLsizei(windowSize.y));
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, textureID, 0);
			glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rboID);
			unBindRenderBuffer();
			unBindTexture();
			unBind();
		}

	}
}