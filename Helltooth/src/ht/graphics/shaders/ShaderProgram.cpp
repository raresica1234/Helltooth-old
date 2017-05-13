#include "ShaderProgram.h"

namespace ht { namespace graphics {
	using namespace maths;
	using namespace utils;

	ShaderProgram::ShaderProgram(String VERTEX_PATH, String FRAGMENT_PATH, bool path)
		: path(path){
		if (path) {
			utils::VFS::resolvePhysicalPath(VERTEX_PATH, this->VERTEX_PATH);
			utils::VFS::resolvePhysicalPath(FRAGMENT_PATH, this->FRAGMENT_PATH);
		}
		else {
			this->VERTEX_PATH = VERTEX_PATH;
			this->FRAGMENT_PATH = FRAGMENT_PATH;
		}
		programID = compile();
		projection = false;

		std::vector<char> stringBuffer;

		GLint numUniforms, maxNameLength = 0;
		glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &numUniforms);
		glGetProgramiv(programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxNameLength);

		stringBuffer.resize(maxNameLength, 0);
		for (GLint i = 0; i < numUniforms; i++) {
			GLint nameLength = 0;
			GLint size = 0; // Used for how many array elements uniform contains
			GLenum type = 0; // Specifies uniform type. float, int, uint, double, vec2, vec3 etc..

			glGetActiveUniform(programID, i, maxNameLength, &nameLength, &size, &type, (GLchar*)stringBuffer.data());
			String name = String(&stringBuffer[0]);

			if (name.substring(name.size - 4) == String("[0]")) {
				name = name.cut(4);
			}

			int location = glGetUniformLocation(programID, name.c_str());
			locations[name] = location;
		}
	}

	ShaderProgram::~ShaderProgram() {
		stop();
		glDeleteProgram(programID);
	}

	int ShaderProgram::compile() {
		GLuint programID = glCreateProgram();

		GLuint vertexID = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
		const char* vertex_Source;
		const char* fragment_Source;
		String vertexSource;
		String fragmentSource;
		if (path) {
			vertexSource = utils::FileUtils::read_file(VERTEX_PATH.c_str());
			fragmentSource = utils::FileUtils::read_file(FRAGMENT_PATH.c_str());
		
			vertex_Source = vertexSource.c_str();
			fragment_Source = fragmentSource.c_str();
		}
		else {
			vertex_Source = VERTEX_PATH.c_str();
			fragment_Source = FRAGMENT_PATH.c_str();
		}
		glShaderSource(vertexID, 1, &vertex_Source, NULL);
		glCompileShader(vertexID);

		GLint result;

		glGetShaderiv(vertexID, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(vertexID, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(vertexID, length, &length, &error[0]);
			HT_FATAL("Failed to compile vertex shader! \n %s", &error[0]);
			glDeleteShader(vertexID);
			return -1;
		}

		glShaderSource(fragmentID, 1, &fragment_Source, NULL);
		glCompileShader(fragmentID);

		glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &result);

		if (result == GL_FALSE) {
			GLint length;
			glGetShaderiv(fragmentID, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> error(length);
			glGetShaderInfoLog(fragmentID, length, &length, &error[0]);
			HT_FATAL("Failed to compile fragment shader! \n %s", &error[0]);
			glDeleteShader(fragmentID);
			return - 1;
		}

		glAttachShader(programID, vertexID);
		glAttachShader(programID, fragmentID);

		glLinkProgram(programID);
		glValidateProgram(programID);

		glDeleteShader(vertexID);
		glDeleteShader(fragmentID);

		return programID;
	}

	void ShaderProgram::start() const { glUseProgram(programID); }
	void ShaderProgram::stop() const { glUseProgram(0); }

	void ShaderProgram::reCompile() {
		stop();
		glDeleteProgram(programID);
		programID = compile();
		projection = false;
	}

} }