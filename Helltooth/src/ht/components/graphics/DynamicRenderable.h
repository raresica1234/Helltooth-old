#pragma once

#include "../../graphics/rendering/Renderable.h"
#include "../../graphics/shaders/ShaderProgram.h"

/*
DynamicRenderable component:
To be used when rendering dynamical entities
This component allows you to submit every frame and render every frame
*/

namespace ht { namespace components { namespace graphics {

			class DynamicRenderable {

			protected:
				ht::graphics::Renderable* renderable;

			public:

				DynamicRenderable() {
					renderable = htnew ht::graphics::Renderable();
				}

				~DynamicRenderable() {
					delete renderable;
				}

				virtual void prepare(ht::graphics::ShaderProgram* program) = 0;

				virtual void render() {
					renderable->render();
				}

			};

} } }