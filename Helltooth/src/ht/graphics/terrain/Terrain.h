#pragma once

#include "../rendering/model/RawModel.h"
#include "../../maths/vec3.h"
#include "../../maths/vec2.h"

#include "../rendering/Renderable.h"
#include "../rendering/types/StaticEntity.h"

#include "../Camera.h"

#include <vector>
namespace ht { namespace graphics {

#define VERTEX_COUNT 128
#define TERRAIN_SIZE 800

	class Terrain : public StaticEntity {
	private:
		ShaderProgram* program;
		
	public:
		Terrain(maths::vec2 location);

		~Terrain();

		void prepare() const;

		void setModelMatrix() const override;

		void setProjection(mat4 projection) const override;

		void setViewMatrix(const Camera *camera) const override;

		void render() const;

		void addBlendMap(Texture* texture);
		
		void addTerrainTextures(Texture* textures, short count = 1);

	};
} }
