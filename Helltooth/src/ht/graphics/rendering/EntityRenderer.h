#pragma once


#include <unordered_map>
#include <vector>

#include "Entity3D.h"
#include "Renderable.h"
#include "../shaders/ShaderProgram.h"
#include "../Camera.h"
#include "../../utils/memory/MemoryManager.h"

namespace ht { namespace graphics {


	class EntityRenderer{
	private:
		//map of Renderables and entites list
		std::unordered_map<Renderable*, std::vector<Entity3D>> entities;
		
		//ShaderProgram
		ShaderProgram* program;

		//Camera
		const Camera* camera;

	public:
		
		//Constructor takes in ShaderProgram
		EntityRenderer(ShaderProgram* program);
		~EntityRenderer();

		//Push entity (Renderable, entity)
		void pushEntity(Renderable* renderable, const Entity3D &entity);

		//Push vector of entities (Renderable, std::vector<Entity3D>)
		void pushEntityList(Renderable* renderable, const std::vector<Entity3D>entities);

		//Render
		void render();

		//set the camera (Should be done only once)
		inline void setCamera(const Camera* camera) { this->camera = camera; }

		//cleaning up at the end of the frame
		void cleanUP();

	};



} }
