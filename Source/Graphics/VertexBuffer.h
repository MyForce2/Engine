#pragma once

#include "GL\glew.h"

namespace Engine {
	namespace Graphics {
		 
		/*
		A class that represent a simple VertexBuffer and handles its creation and deletion
		*/
		class VertexBuffer {
		private:
			GLuint id;
			
		public:
			VertexBuffer();
			VertexBuffer(const void* data, size_t size);
			~VertexBuffer();


			// Binds this buffer
			void bind() const;
			// Unbinds this buffer
			void unBind() const;
			inline const GLuint getID() const { return id; }
		};
	}
}