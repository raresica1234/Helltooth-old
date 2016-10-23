#include "TerrainShader.h"

namespace ht { namespace graphics {

	TerrainShader::TerrainShader(TerrainShaderType type)
		: vertexShader(300, true), fragmentShader(300, true) {

		switch (type) {
		case TILING_SHADER:


			break;
		}

	} 


	TerrainShader::~TerrainShader() {}


} }

