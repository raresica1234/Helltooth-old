#pragma once

#include <GL/glew.h>

#include <math.h>
#include <unordered_map>

#include "tools/VFS/VFS.h"

#include "maths/vec2.h"
#include "maths/vec3.h"
#include "maths/vec4.h"
#include "maths/mat4.h"

#include "utils/Log.h"
#include "utils/String.h"
#include "utils/FileUtils.h"


namespace ht { namespace graphics { 

	class ShaderProgram {
	private:
		//Shader files path
		ht::utils::String VERTEX_PATH;
		ht::utils::String FRAGMENT_PATH;
		
		bool projection;
		bool path;

		//program id
		GLuint programID;

		std::unordered_map<utils::String, unsigned int> locations;

	public:
		//Constructor(vertex shader path, fragment shader path)
		ShaderProgram(ht::utils::String VERTEX_PATH, ht::utils::String FRAGMENT_PATH, bool path = true);
		~ShaderProgram();

		//Uniforms

		__forceinline void uniformBool(utils::String name, const bool& value) { glUniform1f(locations[name], value); }
		__forceinline void uniform1f(utils::String name, const float &value) { glUniform1f(locations[name], value); }
		__forceinline void uniform1i(utils::String name, const int &value) { glUniform1i(locations[name], value); }
		__forceinline void uniform2f(utils::String name, const maths::vec2 &value) { glUniform2f(locations[name], value.x, value.y); }
		__forceinline void uniform3f(utils::String name, const maths::vec3 &value) { glUniform3f(locations[name], value.x, value.y, value.z); }
		__forceinline void uniform4f(utils::String name, const maths::vec4 &value) { glUniform4f(locations[name], value.x, value.y, value.z, value.w); }
		__forceinline void uniformMat4(utils::String name, const maths::mat4 &value) { glUniformMatrix4fv(locations[name], 1, GL_FALSE, value.elements); }
		__forceinline void uniform1iv(utils::String name, const int* value, const short &count) { glUniform1iv(locations[name], count, value); }
		__forceinline void setProjection(utils::String name, const maths::mat4 &value) { glUniformMatrix4fv(locations[name], 1, GL_FALSE, value.elements); projection = true; }

		//Starting the program
		void start() const;

		//Stoping the program
		void stop() const;

		//Recompiles the program
		void reCompile();

		//Tests if the program has a projection matrix bound
		inline bool hasProjection() { return projection; }

	protected:
		int compile();
	};
} } 
