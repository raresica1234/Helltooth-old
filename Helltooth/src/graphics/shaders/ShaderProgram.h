#pragma once

#include <GL/glew.h>

namespace ht { namespace graphics { 

	class ShaderProgram {
	private:
		const char *VERTEX_PATH;
		const char *FRAGMENT_PATH;
		int programID;
		int vertexID, fragmentID;

	public:
		ShaderProgram(const char *VERTEX_PATH, const char *FRAGMENT_PATH);
		~ShaderProgram();

		void start() const;
		void stop() const;

	protected:
		void init();
		void bindAttributes() const;
		int uniformLocation(const char* name) const;
	};

} } 
