#pragma once

#include "assets/Asset.h"

#include "graphics/rendering/model/Cube.h"

#include "graphics/rendering/types/StaticEntity.h"

#include "graphics/textures/Texture.h"

#include "utils/String.h"

namespace ht { namespace graphics {

	enum Face {
		RIGHT = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
		LEFT = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
		TOP = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
		BOTTOM = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
		BACK = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
		FRONT = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
	};

	class Skybox : public StaticEntity {
	private:
		static utils::String skyboxVertex;
		static utils::String skyboxFragment;


		GLuint textureID;

		ShaderProgram* program;

	public:
		Skybox();
		~Skybox();

		void setViewMatrix(maths::mat4 camera) const;
		void setProjection(maths::mat4 projection) const;

		void prepare() const;
		void render() const;

		void addTexture(assets::TextureData* textureData, Face face);
	};

} } 
