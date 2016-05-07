#pragma once

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

	public:
		API(const unsigned int &type, const unsigned int &mode) {
			this->type = type;
			this->mode = mode;
		}

		static bool is3D() {
			return mode == API_MODE_3D;
		}

		static bool is2D() {
			return mode == API_MODE_2D;
		}
	};

} }
