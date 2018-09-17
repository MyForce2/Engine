#pragma once

#include "Shader.h"
#include "Utils\FileUtils.h"
#include "Utils\Log.h"

#include "Math/Vectors/Vectors.h"

namespace Engine {
	namespace Graphics {


		Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
			std::string vertexSource, fragmentSource;
			Utils::readFile(vertexPath, vertexSource);
			Utils::readFile(fragmentPath, fragmentSource);
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
				Utils::Log::getLog()->logError("Compilation failed : " + typeString + "shader");
				std::cout << error << std::endl;
				return 0;
			}
			return shaderID;
		}

		GLint Shader::getUniformLocation(const std::string& name) const {
			GLint location = glGetUniformLocation(id, name.c_str());
			if (location == -1)
				Utils::Log::getLog()->logWarning("Location is -1 for uniform : " + name);
			return location;
		}

		void Shader::setUniformMatrix4fv(const std::string& name, const Math::Mat4& matrix) const {
			GLint location = getUniformLocation(name);
			glUniformMatrix4fv(location, 1, GL_FALSE, &matrix.data[0]);
		}

		void Shader::setInt(const std::string& name, int value) const {
			GLint location = getUniformLocation(name);
			glUniform1i(location, val);
		}

		void Shader::setIVec2(const std::string& name, const Math::IVec2& vec) const {
			GLint location = getUniformLocation(name);
			glUniform2i(location, vec.x, vec.y);
		}

		void Shader::setIVec3(const std::string& name, const Math::IVec3& vec) const {
			GLint location = getUniformLocation(name);
			glUniform3i(location, vec.x, vec.y, vec.z);
		}

		void Shader::setIVec4(const std::string& name, const Math::IVec4& vec) const {
			GLint location = getUniformLocation(name);
			glUniform4i(location, vec.x, vec.y, vec.z, vec.w);
		}

		void Shader::setFloat(const std::string& name, float value) const {
			GLint location = getUniformLocation(name);
			glUniform1f(location, value);
		}

		void Shader::setVec2(const std::string& name, const Math::Vec2& vec) const {
			GLint location = getUniformLocation(name);
			glUniform2f(location, vec.x, vec.y);
		}

		void Shader::setVec3(const std::string& name, const Math::Vec3& vec) const {
			bind();
			GLint location = getUniformLocation(name);
			glUniform3f(location, vec.x, vec.y, vec.z);
			unBind();
		}

		void Shader::setVec4(const std::string& name, const Math::Vec4& vec) const {
			bind();
			GLint location = getUniformLocation(name);
			glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
			unBind();
		}

		void Shader::bindUniformBuffer(const UniformBuffer& ubo, const std::string& name, GLuint blockBinding) const {
			GLuint blockIndex = glGetUniformBlockIndex(id, name.c_str());
			glBindBufferBase(GL_UNIFORM_BUFFER, blockBinding, ubo.getID());
			glUniformBlockBinding(id, blockIndex, blockBinding);
		}
	}
}