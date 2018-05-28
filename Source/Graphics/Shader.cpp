#pragma once

#include "Shader.h"
#include "Utils\FileUtils.h"
#include "Utils\Log.h"

namespace Engine {
	namespace Graphics {


		Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) : locationCache() {
			std::string vertexSource = Utils::readFile(vertexPath);
			std::string fragmentSource = Utils::readFile(fragmentPath);
			id = createProgram(vertexSource, fragmentSource);
			bind();
			
		}

		Shader::~Shader() {
			glDeleteProgram(id);
			unBind();
		}

		void Shader::bind() const {
			glUseProgram(id);
		}

		void Shader::unBind() const {
			glUseProgram(0);
		}

		GLuint Shader::createProgram(const std::string& vertexSource, const std::string& fragmentSource) {
			GLuint program = glCreateProgram();
			GLuint vertex = compileShader(GL_VERTEX_SHADER, vertexSource);
			GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
			glAttachShader(program, vertex);
			glAttachShader(program, fragment);
			glLinkProgram(program);
			glValidateProgram(program);
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			return program;
		}

		GLuint Shader::compileShader(GLuint type, const std::string& source) {
			GLuint shaderID = glCreateShader(type);
			const char* src = source.c_str();
			glShaderSource(shaderID, 1, &src, nullptr);
			glCompileShader(shaderID);
			int status;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE) {
				int length;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
				char* error = new char[length + 1];
				glGetShaderInfoLog(shaderID, length + 1, &length, error);
				std::string typeString = type == GL_FRAGMENT_SHADER ? "Fragment " : "Vertex ";
				Utils::logError("Compilation failed : " + typeString + "shader");
				std::cout << error << std::endl;
				return 0;
			}
			return shaderID;
		}

		GLint Shader::getUniformLocation(const std::string& name) {
			//if (locationCache.find(name) != locationCache.end()) {
			//	return locationCache.at(name);
			//} else {
			//	GLint location = glGetUniformLocation(id, name.c_str());
			//	locationCache[name] = location;
			//	if (location == -1)
			//		Utils::logWarning("Unifrom : " + name + ", location is -1");
			//	return location;
			//}
			GLint location = glGetUniformLocation(id, name.c_str());
			if (location == -1)
				Utils::logWarning("Unifrom : " + name + ", location is -1");
			return location;
		}

		void Shader::setUniformMatrix4fv(const std::string& name, const Math::Mat4& matrix) {
			GLint location = getUniformLocation(name);
			glUniformMatrix4fv(location, 1, GL_FALSE, &matrix.data[0]);
		}

		void Shader::setUniform1i(const std::string& name, int val) {
			GLint location = getUniformLocation(name);
			glUniform1i(location, val);
		}

		void Shader::bindUniformBuffer(const UniformBuffer& ubo, const std::string& name, GLuint blockBinding) const {
			GLuint blockIndex = glGetUniformBlockIndex(id, name.c_str());
			glBindBufferBase(GL_UNIFORM_BUFFER, blockBinding, ubo.getID());
			glUniformBlockBinding(id, blockIndex, blockBinding);
		}
	}
}