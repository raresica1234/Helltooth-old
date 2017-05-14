#pragma once

#include "assets/Asset.h"
#include "assets/ObjLoader.h"

#include "shaders/ShaderManager.h"

#include "rendering/model/RawModel.h"

#include "window/WindowManager.h"

#include "tools/VFS/VFS.h"

#include "utils/String.h"

#define API_MODE_2D 0
#define API_MODE_3D 1

#define API_OPENGL 0
#define API_OPENGLES 1
#define API_DIRECTX 2
#define API_VULKAN 3

namespace ht { namespace graphics {

	class API {
	private:
		static uint32 type;
		static uint32 mode;

		static struct Fog {
			f32 density = 0.007f;
			f32 gradient = 1.5f;
		} fog;

	public:
		API(const uint32& type, const uint32& mode) {
			this->type = type;
			this->mode = mode;
		}

		static RawModel* loadObjFile(utils::String path);
		static assets::Cubemap* loadCubemap(utils::String path);

		static unsigned int createShader(utils::String VERTEX_PATH, utils::String FRAGMENT_PATH, bool path = true);
		static unsigned int createWindow(utils::String title, const uint16 &width, const uint16 &height);

		__forceinline static bool is3D() { return mode == API_MODE_3D; }
		__forceinline static bool is2D() { return mode == API_MODE_2D; }
		__forceinline static Fog getFog() { return fog; }
	};
} }
