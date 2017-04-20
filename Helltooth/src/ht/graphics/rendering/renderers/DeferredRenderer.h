#pragma once

#include "Renderer.h"

#include "graphics/Camera.h"

#include "../types/DynamicEntity.h"
#include "../types/StaticEntity.h"

#include "graphics/rendering/model/Quad.h"

#include "graphics/rendering/GBuffer.h"

#include "graphics/shaders/ShaderManager.h"
#include "graphics/shaders/ShaderProgram.h"

#include "utils/String.h"
#include "utils/memory/MemoryManager.h"

#include "maths/mat4.h"

namespace ht { namespace graphics {

	class DeferredRenderer : public Renderer {
	private:
		GBuffer* gbuffer;
		static utils::String geometryPassVertex;
		static utils::String geometryPassFragment;
		static utils::String basicProgramVert;
		static utils::String basicProgramFrag;


		std::vector<const StaticEntity*> staticEntities;
		std::unordered_map<const Renderable*, std::vector<Entity>> dynamicEntities;
		Window *w;

		ShaderProgram* lightingPass;

		Renderable* quad;

	public:
		DeferredRenderer(Camera* camera);
		~DeferredRenderer();

		void submit(const Entity* entity) override;

		void prepare() override;
		void render() override;
		void cleanUP() override;
		void forceCleanUP() override;
		
		void reloadTextures() override;
	};


} }
