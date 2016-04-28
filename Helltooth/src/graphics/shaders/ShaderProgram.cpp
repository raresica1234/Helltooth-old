#include "ShaderProgram.h"

namespace ht { namespace graphics {

	ShaderProgram::ShaderProgram(const char *VERTEX_PATH, const char *FRAGMENT_PATH) {
		this->VERTEX_PATH = VERTEX_PATH;
		this->FRAGMENT_PATH = FRAGMENT_PATH;
	}

	ShaderProgram::~ShaderProgram() {}

	void ShaderProgram::init() {
	}


} }