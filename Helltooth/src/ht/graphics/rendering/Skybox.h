#pragma once

#include "assets/Asset.h"

#include "graphics/rendering/model/Cube.h"

#include "graphics/rendering/types/StaticEntity.h"

#include "graphics/textures/Texture.h"

#include "utils/String.h"

namespace ht { namespace graphics {

	class Skybox : public StaticEntity {
	private:
		static utils::String skyboxVertex;
		static utils::String skyboxFragment;

		uint32 textureID;

		ShaderProgram* program;

	public:
		Skybox();
		~Skybox();

		void setViewMatrix(maths::mat4 camera) const;
		void setProjection(maths::mat4 projection) const;

		void prepare() const;
		void render() const;

		void addCubemap(assets::Cubemap* cubemap);
	};
} } 
