#pragma once

#include <GL/glew.h>
#include <string>

#include "../../utils/FileUtils.h"
#include "../../maths/vec2.h"
#include "../../maths/vec3.h"
#include "../../maths/vec4.h"
#include "../../maths/mat4.h"


namespace ht { namespace graphics { 

	using namespace maths;

	class ShaderProgram {
	private:
		const char *VERTEX_PATH;
		const char *FRAGMENT_PATH;
		GLuint programID;

	public:
		ShaderProgram(const char *VERTEX_PATH, const char *FRAGMENT_PATH);
		~ShaderProgram();

		void uniform1f(const char *name, const float &value);
		void uniformBool(const char *name, const bool &value);
		void uniform2f(const char *name, const vec2 &value);
		void uniform3f(const char *name, const vec3 &value);
		void uniform4f(const char *name, const vec4 &value);
		void uniformMat4(const char *name, const mat4 &value);


		void start() const;
		void stop() const;

	protected:
		int init();
		int uniformLocation(const char* name) const;
	};

} } 