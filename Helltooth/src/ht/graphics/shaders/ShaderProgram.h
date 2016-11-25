#pragma once

#include <GL/glew.h>

#include "../../utils/FileUtils.h"
#include "../../tools/VFS/VFS.h"
#include "../../maths/vec2.h"
#include "../../maths/vec3.h"
#include "../../maths/vec4.h"
#include "../../maths/mat4.h"

#include "../../utils/Log.h"
#include "../../utils/String.h"

#include <math.h>

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

	public:
		//Constructor(vertex shader path, fragment shader path)
		ShaderProgram(ht::utils::String VERTEX_PATH, ht::utils::String FRAGMENT_PATH, bool path = true);
		~ShaderProgram();

		//Uniforms

		void uniform1f(const char *name, const float &value);
		void uniform1i(const char *name, const int &value);
		void uniformBool(const char *name, const bool &value);
		void uniform2f(const char *name, const ht::maths::vec2 &value);
		void uniform3f(const char *name, const ht::maths::vec3 &value);
		void uniform4f(const char *name, const ht::maths::vec4 &value);
		void uniformMat4(const char *name, const ht::maths::mat4 &value);
		void uniform1iv(const char *name, const int* value, const short &count);
		
		//Sets the projection matrix
		void setProjection(const char *name, const ht::maths::mat4 &value);

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
		GLint uniformLocation(const char* name);
	};
} } 
