#pragma once

#include "../../graphics/rendering/Renderable.h"
#include "../../utils/memory/MemoryManager.h"
#include "../../graphics/shaders/ShaderProgram.h"

/*
StaticRenderable component:
To be used when rendering statical entities
This component allows you to submit once, but render every frame.
*/

namespace ht { namespace components { namespace graphics {

	class StaticRenderable {

	protected:
		ht::graphics::Renderable* renderable;

	public:

		StaticRenderable() {
			renderable = htnew ht::graphics::Renderable();
		}

		~StaticRenderable() {
			delete renderable;
		}

		virtual void prepare(ht::graphics::ShaderProgram* program) = 0;

		virtual void render() {
			renderable->render();
		}

	};

} } }
