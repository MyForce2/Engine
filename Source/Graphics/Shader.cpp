#pragma once

#include "Shader.h"
#include "Utils\FileUtils.h"
#include "Utils\Log.h"

#include "Math/Vectors/Vectors.h"

namespace Engine {
	namespace Graphics {

		using namespace Utils;

		Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
			std::string vertexSource, fragmentSource;
			Utils::readFile(vertexPath, vertexSource);
			Utils::readFile(fragmentPath, fragmentSource);
			id = createProgram(vertexSource, fragmentSource);
			if (id == 0)
				Log::getLog()->logError("Failed to create OpenGL program : ");
			else
				Log::getLog()->logInfo("Created OpenGL program : ");
			Log::getLog()->logInfo("Vertex path : " + vertexPath);
			Log::getLog()->logInfo("Fragment path : " + fragmentPath);
			bind();
		}

		Shader::Shader(const std::string& vertexPath, const std::string& geometryPath, const std::string& fragmentPath) {
			std::string vertexSource, geometrySource, fragmentSource;
			Utils::readFile(vertexPath, vertexSource);
			Utils::readFile(geometryPath, geometrySource);
			Utils::readFile(fragmentPath, fragmentSource);
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
			GLint linkingStatus, validationStatus;
			glAttachShader(program, vertex);
			glAttachShader(program, fragment);
			glLinkProgram(program);
			glGetProgramiv(program, GL_LINK_STATUS, &linkingStatus);
			if (linkingStatus == GL_FALSE) {
				GLint length;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
				GLchar* error = new char[length + 1]();
				glGetProgramInfoLog(program, length + 1, &length, error);
				Log::getLog()->logError("Shader program (ID = " + std::to_string(program) + ") linking failed");
				Log::getLog()->logError("Shader linking errors : " + std::string(error));
				std::cout << "Shader linking error : " << '\n' << error << std::endl;
				delete[] error;
				return 0;
			}
			glValidateProgram(program);
			glGetProgramiv(program, GL_VALIDATE_STATUS, &validationStatus);
			if (validationStatus == GL_FALSE) {
				GLint length;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
				GLchar* error = new char[length + 1]();
				glGetProgramInfoLog(program, length + 1, &length, error);
				Log::getLog()->logError("Shader program (ID = " + std::to_string(program) + ") validation failed");
				Log::getLog()->logError("Shader validation errors : " + std::string(error));
				std::cout << "Shader validation error : " << '\n' << error << std::endl;
				delete[] error;
				return 0;
			}
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			return program;
		}

		GLuint Shader::createProgram(const std::string& vertexSource, const std::string& geometrySource, const std::string& fragmentSource) {
			GLuint program = glCreateProgram();
			GLuint vertex = compileShader(GL_VERTEX_SHADER, vertexSource);
			GLuint geometry = compileShader(GL_GEOMETRY_SHADER, geometrySource);
			GLuint fragment = compileShader(GL_FRAGMENT_SHADER, fragmentSource);
			GLint linkingStatus, validationStatus;
			glAttachShader(program, vertex);
			glAttachShader(program, geometry);
			glAttachShader(program, fragment);
			glLinkProgram(program);
			glGetProgramiv(program, GL_LINK_STATUS, &linkingStatus);
			if (linkingStatus == GL_FALSE) {
				GLint length;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
				GLchar* error = new char[length + 1]();
				glGetProgramInfoLog(program, length + 1, &length, error);
				Log::getLog()->logError("Shader program (ID = " + std::to_string(program) + ") linking failed");
				Log::getLog()->logError("Shader linking errors : " + std::string(error));
				std::cout << "Shader linking error : " << '\n' << error << std::endl;
				delete[] error;
				return 0;
			}
			glValidateProgram(program);
			glGetProgramiv(program, GL_VALIDATE_STATUS, &validationStatus);
			if (validationStatus == GL_FALSE) {
				GLint length;
				glGetProgramiv(program, GL_INFO_LOG_LENGTH, &length);
				GLchar* error = new char[length + 1]();
				glGetProgramInfoLog(program, length + 1, &length, error);
				Log::getLog()->logError("Shader program (ID = " + std::to_string(program) + ") validation failed");
				Log::getLog()->logError("Shader validation errors : " + std::string(error));
				std::cout << "Shader validation error : " << '\n' << error << std::endl;
				delete[] error;
				return 0;
			}
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			glDeleteShader(geometry);
			return program;
		}

		GLuint Shader::compileShader(GLuint type, const std::string& source) {
			GLuint shaderID = glCreateShader(type);
			const char* src = source.c_str();
			glShaderSource(shaderID, 1, &src, nullptr);
			glCompileShader(shaderID);
			GLint status;
			glGetShaderiv(shaderID, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE) {
				GLint length;
				glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &length);
				GLchar* error = new char[length + 1]();
				glGetShaderInfoLog(shaderID, length + 1, &length, error);
				std::string typeString = type == GL_FRAGMENT_SHADER ? "Fragment " : type == GL_GEOMETRY_SHADER ? "Geometry " : "Vertex ";
				Log::getLog()->logError("Compilation failed : " + typeString + "shader");
				Log::getLog()->logError("Compilation error : " + std::string(error));
				std::cout << error << std::endl;
				delete[] error;
				return 0;
			}
			return shaderID;
		}

		GLint Shader::getUniformLocation(const std::string& name) const {
			bind();
			GLint location = glGetUniformLocation(id, name.c_str());
			if (location == -1)
				Log::getLog()->logWarning("Location is -1 for uniform : " + name);
			return location;
		}

		void Shader::setUniformMatrix4fv(const std::string& name, const Math::Mat4& matrix) const {
			GLint location = getUniformLocation(name);
			glUniformMatrix4fv(location, 1, GL_FALSE, &matrix.data[0]);
			unBind();
		}

		void Shader::setInt(const std::string& name, int value) const {
			GLint location = getUniformLocation(name);
			glUniform1i(location, value);
			unBind();
		}

		void Shader::setIVec2(const std::string& name, const Math::IVec2& vec) const {
			GLint location = getUniformLocation(name);
			glUniform2i(location, vec.x, vec.y);
			unBind();
		}

		void Shader::setIVec3(const std::string& name, const Math::IVec3& vec) const {
			GLint location = getUniformLocation(name);
			glUniform3i(location, vec.x, vec.y, vec.z);
			unBind();
		}

		void Shader::setIVec4(const std::string& name, const Math::IVec4& vec) const {
			GLint location = getUniformLocation(name);
			glUniform4i(location, vec.x, vec.y, vec.z, vec.w);
			unBind();
		}

		void Shader::setFloat(const std::string& name, float value) const {
			GLint location = getUniformLocation(name);
			glUniform1f(location, value);
			unBind();
		}

		void Shader::setVec2(const std::string& name, const Math::Vec2& vec) const {
			GLint location = getUniformLocation(name);
			glUniform2f(location, vec.x, vec.y);
			unBind();
		}

		void Shader::setVec3(const std::string& name, const Math::Vec3& vec) const {
			GLint location = getUniformLocation(name);
			glUniform3f(location, vec.x, vec.y, vec.z);
			unBind();
		}

		void Shader::setVec4(const std::string& name, const Math::Vec4& vec) const {
			GLint location = getUniformLocation(name);
			glUniform4f(location, vec.x, vec.y, vec.z, vec.w);
			unBind();
		}

		void Shader::bindUniformBuffer(const UniformBuffer& ubo, const std::string& name, GLuint blockBinding) const {
			bind();
			GLuint blockIndex = glGetUniformBlockIndex(id, name.c_str());
			glBindBufferBase(GL_UNIFORM_BUFFER, blockBinding, ubo.getID());
			glUniformBlockBinding(id, blockIndex, blockBinding);
			unBind();
		}
	}
}