#pragma once

#include "../assets/Asset.h"
#include "../assets/ObjLoader.h"

#include "shaders/ShaderManager.h"
#include "rendering/model/RawModel.h"
#include "window/WindowManager.h"

#include "../tools/VFS/VFS.h"

#include "../utils/String.h"

#define API_MODE_2D 0
#define API_MODE_3D 1

#define API_OPENGL 0
#define API_OPENGLES 1
#define API_DIRECTX 2
#define API_VULKAN 3

namespace ht { namespace graphics {

	class API {
	private:
		static unsigned int type;
		static unsigned int mode;

		static struct Fog {
			float density = 0.007f;
			float gradient = 1.5f;
		} fog;

	public:
		API(const unsigned int& type, const unsigned int& mode) {
			this->type = type;
			this->mode = mode;
		}

		static RawModel* loadObjFile(ht::utils::String path);

		static unsigned int createShader(ht::utils::String VERTEX_PATH, ht::utils::String FRAGMENT_PATH, bool path = true);
		static unsigned int createWindow(ht::utils::String title, const int &width, const int &height);

		__forceinline static bool is3D() { return mode == API_MODE_3D; }
		__forceinline static bool is2D() { return mode == API_MODE_2D; }
		__forceinline static Fog getFog() { return fog; }
	};
} }
