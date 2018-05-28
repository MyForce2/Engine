#pragma once

#include <GL\glew.h>
#include <string>

#include "Math\Mat4.h"
#include "UniformBuffer.h"
#include <unordered_map>



namespace Engine {
	namespace Graphics {
		/*
		Manages a shader object
		*/
		class Shader {
		public:
			GLuint id;
			std::unordered_map<std::string, GLint> locationCache;

		public:
			Shader(const std::string& vertexPath, const std::string& fragmentPath);
			~Shader();

			void bind() const;
			void unBind() const;

			// All methods to set uniforms

			void setUniformMatrix4fv(const std::string& name, const Math::Mat4& matrix);
			void setUniform1i(const std::string& name, int val);

			// Binds a uniform buffer to the specified index (blockBinding = index)
			void bindUniformBuffer(const UniformBuffer& ubo, const std::string& name, GLuint blockBinding) const;
		private:
			// Compiles a shader and returnes its id, returns 0 if compilation failed
			static GLuint compileShader(GLuint type, const std::string& source);
			// Creates a program with the two shaders attached, and returns its id
			static GLuint createProgram(const std::string& vertexSource, const std::string& fragmentSource);
			// Returns the location in memory of the given uniform
			GLint getUniformLocation(const std::string& name);
		};
	}
}