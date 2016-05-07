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

		ShaderProgram *program;

	public:
		BatchRenderer(Renderable *renderable, ShaderProgram *program);
		
		~BatchRenderer();

		void addEntity(Entity3D entity);
		void deleteEntity(Entity3D entity);

		void prepare();
		
		void render() const;



	};


} }
