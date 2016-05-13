#pragma once

#include <vector>

#include "Entity3D.h"
#include "../API.h"
#include "../shaders/ShaderProgram.h"


namespace ht { namespace graphics {

	class BatchRenderer {
	private:
		std::vector<Entity3D> entities;

		Renderable *renderable;
		Renderable *object;

		ShaderProgram *program;

		vec3 *objectPositions;
		const GLint *objectIndices;

		GLsizei objectPositionCount;

		unsigned int entityCount = 0;

		GLfloat *positions;
		GLsizei positionSize;

		GLint *indices;
		GLsizei indicesSize;

		GLfloat *normals;
		GLfloat *textureCoords;

		bool changed;

	public:
		BatchRenderer(Renderable *object, ShaderProgram *program);
		
		~BatchRenderer();

		void addEntity(Entity3D entity);
		void deleteEntity(Entity3D entity);

		void prepare();
		
		void render() const;

	protected:
		void reInit();


	};


} }
