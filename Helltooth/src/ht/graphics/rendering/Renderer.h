#pragma once

#include "Entity3D.h"
#include "Renderable.h"


namespace ht{ namespace graphics {

	class Renderer {
	public:

		virtual void pushEntity(Renderable* renderable, const Entity3D &entity) = 0;

		virtual void render() = 0;

	};


} }
