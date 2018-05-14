#pragma once

#include <GL\glew.h>
#include <string>




namespace Engine {
	namespace Graphics {
		/*
		Manages a shader object
		*/
		class Shader {
		private:
			GLuint id;

		public:
			Shader(const std::string& vertexPath, const std::string& fragmentPath);
			~Shader();

			void bind() const;
			void unBind() const;

		private:
			// Compiles a shader and returnes its id, returns 0 if compilation failed
			static GLuint compileShader(GLuint type, const std::string& source);
			// Creates a program with the two shaders attached, and returns its id
			static GLuint createProgram(const std::string& vertexSource, const std::string& fragmentSource);
		};
	}
}