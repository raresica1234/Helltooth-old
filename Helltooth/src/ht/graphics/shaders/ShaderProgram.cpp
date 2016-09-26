#include "ShaderProgram.h"

namespace ht { namespace graphics {
	using namespace maths;

	ShaderProgram::ShaderProgram(const char *VERTEX_PATH, const char *FRAGMENT_PATH, bool path) 
		: VERTEX_PATH(VERTEX_PATH), FRAGMENT_PATH(FRAGMENT_PATH), path(path){
		programID = compile();
		projection = false;
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
		std::string vertexSource;
		std::string fragmentSource;
		if (path) {
			vertexSource = utils::FileUtils::read_file(VERTEX_PATH);
			fragmentSource = utils::FileUtils::read_file(FRAGMENT_PATH);
		
			vertex_Source = vertexSource.c_str();
			fragment_Source = fragmentSource.c_str();
		}
		else {
			vertexSource = std::string(VERTEX_PATH);
			fragmentSource = std::string(FRAGMENT_PATH);

			vertex_Source = vertexSource.c_str();
			fragment_Source = fragmentSource.c_str();
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

	GLint ShaderProgram::uniformLocation(const char* location) {
		return glGetUniformLocation(programID, location);
	}

	void ShaderProgram::uniformBool(const char* name, const bool& value) { glUniform1f(uniformLocation(name), value); }

	void ShaderProgram::uniform1f(const char *name, const float &value) { glUniform1f(uniformLocation(name), value); }
	void ShaderProgram::uniform1i(const char *name, const int &value) { glUniform1i(uniformLocation(name), value); }
	void ShaderProgram::uniform2f(const char *name, const vec2 &value) { glUniform2f(uniformLocation(name), value.x, value.y); }
	void ShaderProgram::uniform3f(const char *name, const vec3 &value) { glUniform3f(uniformLocation(name), value.x, value.y, value.z); }
	void ShaderProgram::uniform4f(const char *name, const vec4 &value) { glUniform4f(uniformLocation(name), value.x, value.y, value.z, value.w); }
	void ShaderProgram::uniformMat4(const char *name, const mat4 &value) { glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE, value.elements); }

	void ShaderProgram::uniform1iv(const char *name, const int* value, const short &count) {
		glUniform1iv(uniformLocation(name), count, value);
	}

	void ShaderProgram::setProjection(const char *name, const mat4 &value) { glUniformMatrix4fv(uniformLocation(name), 1, GL_FALSE, value.elements); projection = true; }
	
	void ShaderProgram::setLight(const char *name, const Light &light) {
		uniform3f((std::string(name) + "Pos").c_str(), light.getPosition());
		uniform3f((std::string(name) + "Color").c_str(), light.getColor());
	}

	void ShaderProgram::setSun(const char *name, const Sun &sun) {
		uniform3f(name, sun.getPosition());
	}

} }