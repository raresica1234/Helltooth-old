#pragma once


#include <unordered_map>
#include <vector>

#include "Entity3D.h"
#include "Renderable.h"

#include "../shaders/ShaderProgram.h"
#include "../Camera.h"
#include "../../utils/memory/MemoryManager.h"

namespace ht { namespace graphics {


	class EntityRenderer3D{
	private:
		//map of Renderables and entites list
		std::unordered_map<const Renderable*, std::vector<Entity3D>> entities;
		
		//ShaderProgram
		ShaderProgram* program;

		//Camera
		const Camera* camera;

	public:
		
		//Constructor takes in ShaderProgram
		EntityRenderer3D(ShaderProgram* program);
		~EntityRenderer3D();

		//Push entity (Renderable, entity)
		void submit(const Renderable* renderable, const Entity3D &entity);

		//Push vector of entities (Renderable, std::vector<Entity3D>)
		void submit(const Renderable* renderable, const std::vector<Entity3D>entities);

		//Render
		void render();

		//set the camera (Should be done only once)
		inline void setCamera(const Camera* camera) { this->camera = camera; }

		//cleaning up at the end of the frame
		void cleanUP();

	};



} }
