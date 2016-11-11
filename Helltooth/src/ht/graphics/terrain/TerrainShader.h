#pragma once

#include <string>

#include "../shaders/DynamicShader.h"

namespace ht { namespace graphics {

	enum TerrainShaderType {
		TILING_SHADER,
		FOUR_CHANNEL_BLEND_MAP_SHADER,
	};

	class TerrainShader {
	private:
		DynamicShader vertexShader;
		DynamicShader fragmentShader;

	public:
		TerrainShader(TerrainShaderType type = TILING_SHADER);
		~TerrainShader();

		inline std::string generateVertex() { return vertexShader.toString(); }
		inline std::string generateFragment() { return fragmentShader.toString(); }

	};


} }