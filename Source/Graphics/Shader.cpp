#pragma once

#include "Shader.h"
#include "Utils\FileUtils.h"

namespace Engine {
	namespace Graphics {


		Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) {
			std::string vertexSource = Utils::readFile(vertexPath);
			std::string fragmentSource = Utils::readFile(fragmentPath);
			id = createProgram(vertexSource, fragmentSource);
			bind();
		}

		Shader::~Shader() {
			glDeleteProgram(id);
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
			glValidateProgram(program);
			glDeleteShader(vertex);
			glDeleteShader(fragment);
			return program;
		}

		GLuint Shader::compileShader(GLuint type, const std::string& source) {
			GLuint id = glCreateShader(type);
			const char* src = source.c_str();
			glShaderSource(id, 1, &src, nullptr);
			glCompileShader(id);
			int status;
			glGetShaderiv(id, GL_COMPILE_STATUS, &status);
			if (status == GL_FALSE) {
				int length;
				glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
				char* error = new char[length + 1];
				glGetShaderInfoLog(id, length + 1, &length, error);
				std::cout << "Compilation failed : " << (type == GL_FRAGMENT_SHADER ? "Fragment " : "Shader ") << "shader" << std::endl;
				std::cout << error << std::endl;
				return 0;
			}
			return id;
		}
	}
}