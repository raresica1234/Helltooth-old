#pragma once

#include <GL/glew.h>

#include "../../utils/FileUtils.h"
#include "../../maths/vec2.h"
#include "../../maths/vec3.h"
#include "../../maths/vec4.h"
#include "../../maths/mat4.h"

#include "../../utils/Log.h"
#include "../lighting/Light.h"
#include "../lighting/Sun.h"

#include <unordered_map>
#include <string>

#include <math.h>

namespace ht { namespace graphics { 

	using namespace maths;


	class ShaderProgram {
	private:
		//Shader files path
		const char *VERTEX_PATH;
		const char *FRAGMENT_PATH;
		
		bool projection;

		//program id
		GLuint programID;

	public:
		//Constructor(vertex shader path, fragment shader path)
		ShaderProgram(const char *VERTEX_PATH, const char *FRAGMENT_PATH);
		~ShaderProgram();

		//Uniforms

		void uniform1f(const char *name, const float &value);
		void uniform1i(const char *name, const int &value);
		void uniformBool(const char *name, const bool &value);
		void uniform2f(const char *name, const vec2 &value);
		void uniform3f(const char *name, const vec3 &value);
		void uniform4f(const char *name, const vec4 &value);
		void uniformMat4(const char *name, const mat4 &value);
		void uniform1iv(const char *name, const int* value, const short &count);
		
		void setProjection(const char *name, const mat4 &value);
		
		void setLight(const char *name, const Light &light);
		void setSun(const char *name, const Sun &sun);

		//Starting the program
		void start() const;

		//Stoping the program
		void stop() const;

		inline void reCompile() {
			stop();
			glDeleteProgram(programID);
			programID = compile();
			projection = false;
		}

		inline bool hasProjection() { return projection; }

	protected:
		int compile();
		GLint uniformLocation(const char* name);
	};

} } 
